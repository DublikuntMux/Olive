#include <olive.h>
#include <stdint.h>

/**
* @brief Blend a rectangular area of the sprite onto the canvas. This is useful for drawing things that are part of a sprite such as textures or text - to - be - drawn in an OpenLivec - compatible way.
* @param oc The canvas to blit onto. Mustn't be null.
* @param x The x coordinate of the area to blend.
* @param y The y coordinate of the area to blend.
* @param w The width of the area to blend.
* @param h The height of the area to blend.
* @param sprite The sprite to blend onto oc. Mustn't be null
*/
void olivec_sprite_blend(Olivec_Canvas oc, int x, int y, int w, int h,
                         Olivec_Canvas sprite) {
  // Returns true if the sprite is not in the width of the sprite.
  if (sprite.width == 0)
    return;
  // Returns true if the sprite is not in the current size.
  if (sprite.height == 0)
    return;

  Olivec_Normalized_Rect nr = {0};
  // Normalize rectangle to the nearest rectangle.
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;

  int xa = nr.ox1;
  // Set the x y value to the first point of the box
  if (w < 0)
    xa = nr.ox2;
  int ya = nr.oy1;
  // Set y coordinate to y coordinate
  if (h < 0)
    ya = nr.oy2;
  // Draw the sprite in the blending mode.
  for (int y = nr.y1; y <= nr.y2; ++y) {
    // Draw the sprite in the blending mode.
    for (int x = nr.x1; x <= nr.x2; ++x) {
      size_t nx = (x - xa) * ((int)sprite.width) / w;
      size_t ny = (y - ya) * ((int)sprite.height) / h;
      olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), OLIVEC_PIXEL(sprite, nx, ny));
    }
  }
}

/**
* @brief Copy a rectangular area of the sprite onto the canvas. This is useful for copying an image to a different location in the same rendering context.
* @param oc The canvas to copy onto. Must have Olivec_Canvas :: type == OLVEC_SPRITE
* @param x The x coordinate
* @param y
* @param w
* @param h
* @param sprite
*/
void olivec_sprite_copy(Olivec_Canvas oc, int x, int y, int w, int h,
                        Olivec_Canvas sprite) {
  // Returns true if the sprite is not in the width of the sprite.
  if (sprite.width == 0)
    return;
  // Returns true if the sprite is not in the current size.
  if (sprite.height == 0)
    return;

  // TODO: consider introducing flip parameter instead of relying on negative
  // width and height Similar to how SDL_RenderCopyEx does that
  Olivec_Normalized_Rect nr = {0};
  // Normalize rectangle to the nearest rectangle.
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;

  int xa = nr.ox1;
  // Set the x y value to the first point of the box
  if (w < 0)
    xa = nr.ox2;
  int ya = nr.oy1;
  // Set y coordinate to y coordinate
  if (h < 0)
    ya = nr.oy2;
  // Draw the sprite in the area of the sprite.
  for (int y = nr.y1; y <= nr.y2; ++y) {
    // Draw the sprite in the area of the sprite.
    for (int x = nr.x1; x <= nr.x2; ++x) {
      size_t nx = (x - xa) * ((int)sprite.width) / w;
      size_t ny = (y - ya) * ((int)sprite.height) / h;
      OLIVEC_PIXEL(oc, x, y) = OLIVEC_PIXEL(sprite, nx, ny);
    }
  }
}

// TODO: olivec_pixel_bilinear does not check for out-of-bounds
/**
* @brief Return a pixel value from a rectangular area. The rectangle is divided equally into w and h parts and the result is clipped to the range [ 0 1 ]
* @param sprite The canvas to draw from
* @param nx The x coordinate of the pixel to draw.
* @param ny The y coordinate of the pixel to draw.
* @param w The width of the rectangle. This is the number of pixels that will be drawn in the sprite.
* @param h The height of the rectangle. This is the number of pixels that will be drawn in the sprite.
* @return The pixel value in the form of a uint32_t value which can be used as a color
*/
uint32_t olivec_pixel_bilinear(Olivec_Canvas sprite, int nx, int ny, int w,
                               int h) {
  int px = nx % w;
  int py = ny % h;

  int x1 = nx / w, x2 = nx / w;
  int y1 = ny / h, y2 = ny / h;
  // Find the x coordinate of the sprite.
  if (px < w / 2) {
    // left
    px += w / 2;
    x1 -= 1;
    // Set x1 to 0 to 0
    if (x1 < 0)
      x1 = 0;
  } else {
    // right
    px -= w / 2;
    x2 += 1;
    // Find the x coordinate of the sprite.
    if ((size_t)x2 >= sprite.width)
      x2 = sprite.width - 1;
  }

  // Find the y coordinate of the top and bottom of the sprite.
  if (py < h / 2) {
    // top
    py += h / 2;
    y1 -= 1;
    // Set y1 to 0 to the bottom of the y axis.
    if (y1 < 0)
      y1 = 0;
  } else {
    // bottom
    py -= h / 2;
    y2 += 1;
    // Find the y coordinate of the sprite.
    if ((size_t)y2 >= sprite.height)
      y2 = sprite.height - 1;
  }

  return mix_colors2(mix_colors2(OLIVEC_PIXEL(sprite, x1, y1),
                                 OLIVEC_PIXEL(sprite, x2, y1), px, w),
                     mix_colors2(OLIVEC_PIXEL(sprite, x1, y2),
                                 OLIVEC_PIXEL(sprite, x2, y2), px, w),
                     py, h);
}

/**
* @brief Copy a bilinear part of the sprite. This is a convenience function for copying an image to a canvas without using a pre - allocated buffer.
* @param oc The canvas to copy to. Must be non - null.
* @param x The x coordinate of the top - left corner of the copy.
* @param y The y coordinate of the top - left corner of the copy.
* @param w The width of the copy. If w < 0 the rectangle is not copied.
* @param h The height of the copy. If h < 0 the rectangle is not copied
* @param sprite
*/
void olivec_sprite_copy_bilinear(Olivec_Canvas oc, int x, int y, int w, int h,
                                 Olivec_Canvas sprite) {
  // TODO: support negative size in olivec_sprite_copy_bilinear()
  // Returns true if w 0.
  if (w <= 0)
    return;
  // Returns true if h is less than zero.
  if (h <= 0)
    return;

  Olivec_Normalized_Rect nr = {0};
  // Normalize rectangle to the nearest rectangle.
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;

  // Draw all the pixels in the sprite.
  for (int y = nr.y1; y <= nr.y2; ++y) {
    // Draw a bilinear of the sprite.
    for (int x = nr.x1; x <= nr.x2; ++x) {
      size_t nx = (x - nr.ox1) * sprite.width;
      size_t ny = (y - nr.oy1) * sprite.height;
      OLIVEC_PIXEL(oc, x, y) = olivec_pixel_bilinear(sprite, nx, ny, w, h);
    }
  }
}
