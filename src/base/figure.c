#include "olive/base/figure.h"
#include "olive/base/color.h"
#include "olive/base/tringle.h"
#include "olive/olive.h"
#include <stdint.h>

/**
 * @brief Draw a rectangle. This is equivalent to drawing a filled rectangle
 * with the given color on the Olivec_Canvas.
 * @param oc The canvas to draw on. Must have been initialized.
 * @param x The x coordinate of the rectangle. This is in canvas coordinates.
 * @param y The y coordinate of the rectangle. This is in canvas coordinates.
 * @param w The width of the rectangle. This is in canvas coordinates.
 * @param h The height of the rectangle. This is in canvas coordinates.
 * @param color The color to draw the rectangle with. This is in pixel values
 */
void olivec_rect(Olivec_Canvas oc, int x, int y, int w, int h, uint32_t color) {
  Olivec_Normalized_Rect nr = {0};
  // Normalize rectangle to the nearest rectangle.
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;
  // Draw the blending of the blending area
  for (int i = nr.x1; i <= nr.x2; ++i) {
    // Draw the color of the blending area
    for (int ii = nr.y1; ii <= nr.y2; ++ii) {
      olivec_blend_color(&OLIVEC_PIXEL(oc, i, ii), color);
    }
  }
}

/**
 * @brief Normalize a rectangle to fit the canvas. This is useful for rendering
 * rectangles that are in a different coordinate system than the one used to
 * render the canvas.
 * @param x X coordinate of the rectangle to normalize. This is relative to the
 * canvas
 * @param y Y coordinate of the rectangle to normalize. This is relative to the
 * canvas
 * @param w Width of the rectangle to normalize. This is relative to the canvas
 * @param h Height of the rectangle to normalize. This is relative to the canvas
 * @param canvas_width Width of the canvas to normalize to. If 0 no scaling is
 * done.
 * @param canvas_height Height of the canvas to normalize to. If 0 no scaling is
 * done.
 * @param nr
 * @return True if the rectangle was normalized false otherwise. In this case
 * \ a nr is modified in - place
 */
bool olivec_normalize_rect(int x, int y, int w, int h, size_t canvas_width,
                           size_t canvas_height, Olivec_Normalized_Rect *nr) {
  // No need to render empty rectangle
  // Returns true if w 0.
  if (w == 0)
    return false;
  // Returns true if the height is zero.
  if (h == 0)
    return false;

  nr->ox1 = x;
  nr->oy1 = y;

  // Convert the rectangle to 2-points representation
  nr->ox2 = nr->ox1 + OLIVEC_SIGN(int, w) * (OLIVEC_ABS(int, w) - 1);
  // Swap the current value of the two sets of objects
  if (nr->ox1 > nr->ox2)
    OLIVEC_SWAP(int, nr->ox1, nr->ox2);
  nr->oy2 = nr->oy1 + OLIVEC_SIGN(int, h) * (OLIVEC_ABS(int, h) - 1);
  // Swaps the yoy of the two axes
  if (nr->oy1 > nr->oy2)
    OLIVEC_SWAP(int, nr->oy1, nr->oy2);

  // Check if the canvas is in the canvas width
  if (nr->ox1 >= (int)canvas_width)
    return false;
  // Returns true if the number of objects in the array is less than 0
  if (nr->ox2 < 0)
    return false;
  // Check if the canvas is within the canvas height
  if (nr->oy1 >= (int)canvas_height)
    return false;
  // Returns true if nr yoy2 0 if nr yoy2 0
  if (nr->oy2 < 0)
    return false;

  nr->x1 = nr->ox1;
  nr->y1 = nr->oy1;
  nr->x2 = nr->ox2;
  nr->y2 = nr->oy2;

  // Clamp the rectangle to the boundaries
  // Set the number of bits to 0.
  if (nr->x1 < 0)
    nr->x1 = 0;
  // Set the x2 coordinate of the canvas.
  if (nr->x2 >= (int)canvas_width)
    nr->x2 = (int)canvas_width - 1;
  // Set the y1 to 0.
  if (nr->y1 < 0)
    nr->y1 = 0;
  // Set the y2 coordinate of the canvas.
  if (nr->y2 >= (int)canvas_height)
    nr->y2 = (int)canvas_height - 1;

  return true;
}

/**
 * @brief Draw a rectangular frame. This is the same as drawing a rectangle with
 * center at ( x y ) and width and height w and height h.
 * @param oc The canvas to draw on. Must have Olivec_Canvas :: draw () called
 * before.
 * @param x The x coordinate of the top left corner of the frame.
 * @param y The y coordinate of the top left corner of the frame.
 * @param w The width of the frame. If 0 nothing is drawn.
 * @param h The height of the frame. If 0 nothing is drawn.
 * @param t The time in milliseconds to draw the frame.
 * @param color The color of the frame in hexidecimal
 */
void olivec_frame(Olivec_Canvas oc, int x, int y, int w, int h, size_t t,
                  uint32_t color) {
  // If t is 0 return false.
  if (t == 0)
    return; // Nothing to render

  // Convert the rectangle to 2-points representation
  int x1 = x;
  int y1 = y;
  int x2 = x1 + OLIVEC_SIGN(int, w) * (OLIVEC_ABS(int, w) - 1);
  // x1 x2 if x1 x2
  if (x1 > x2)
    OLIVEC_SWAP(int, x1, x2);
  int y2 = y1 + OLIVEC_SIGN(int, h) * (OLIVEC_ABS(int, h) - 1);
  // Swaps the given y value.
  if (y1 > y2)
    OLIVEC_SWAP(int, y1, y2);

  olivec_rect(oc, x1 - t / 2, y1 - t / 2, (x2 - x1 + 1) + t / 2 * 2, t,
              color); // Top
  olivec_rect(oc, x1 - t / 2, y1 - t / 2, t, (y2 - y1 + 1) + t / 2 * 2,
              color); // Left
  olivec_rect(oc, x1 - t / 2, y2 + t / 2, (x2 - x1 + 1) + t / 2 * 2, -t,
              color); // Bottom
  olivec_rect(oc, x2 + t / 2, y1 - t / 2, -t, (y2 - y1 + 1) + t / 2 * 2,
              color); // Right
}

/**
 * @brief Draw an ellipse. This is a helper function for olivec_draw_ellipse ().
 * @param oc The canvas to draw on. This must be initialized.
 * @param cx The x coordinate of the center of the ellipse.
 * @param cy The y coordinate of the center of the ellipse.
 * @param rx The x coordinate of the ellipse's center in the x direction.
 * @param ry The y coordinate of the ellipse's center in the y direction.
 * @param color The color of the ellipse in the color space
 */
void olivec_ellipse(Olivec_Canvas oc, int cx, int cy, int rx, int ry,
                    uint32_t color) {
  Olivec_Normalized_Rect nr = {0};
  int rx1 = rx + OLIVEC_SIGN(int, rx);
  int ry1 = ry + OLIVEC_SIGN(int, ry);
  // Normalize rectangle to the nearest rectangle.
  if (!olivec_normalize_rect(cx - rx1, cy - ry1, 2 * rx1, 2 * ry1, oc.width,
                             oc.height, &nr))
    return;

  // Draw the OLIVEC color.
  for (int y = nr.y1; y <= nr.y2; ++y) {
    // Draw the color of the surface
    for (int x = nr.x1; x <= nr.x2; ++x) {
      float nx = (x + 0.5 - nr.x1) / (2.0f * rx1);
      float ny = (y + 0.5 - nr.y1) / (2.0f * ry1);
      float dx = nx - 0.5;
      float dy = ny - 0.5;
      // Set the color of the ellipse
      if (dx * dx + dy * dy <= 0.5 * 0.5) {
        OLIVEC_PIXEL(oc, x, y) = color;
      }
    }
  }
}

/**
 * @brief Draw a circle on the canvas. This is a convenience function for
 * drawing circles that are very close to each other in the draw_circle
 * function.
 * @param oc The canvas to draw on. Must have Olivec_Canvas initialized.
 * @param cx The x coordinate of the center of the circle.
 * @param cy The y coordinate of the center of the circle.
 * @param r The radius of the circle. It must be positive or negative.
 * @param color The color of the circle in hex format 0xRRGGBB
 */
void olivec_circle(Olivec_Canvas oc, int cx, int cy, int r, uint32_t color) {
  Olivec_Normalized_Rect nr = {0};
  int r1 = r + OLIVEC_SIGN(int, r);
  // Normalize rectangle to nearest nearest rectangle.
  if (!olivec_normalize_rect(cx - r1, cy - r1, 2 * r1, 2 * r1, oc.width,
                             oc.height, &nr))
    return;

  // Draw the color of the blending area.
  for (int y = nr.y1; y <= nr.y2; ++y) {
    // Draw the color of the blending area.
    for (int x = nr.x1; x <= nr.x2; ++x) {
      int count = 0;
      // Find the number of times the probability of overflow is less than or
      // equal to the probability of overflow.
      for (int sox = 0; sox < OLIVEC_AA_RES; ++sox) {
        // Find the probability of overflow.
        for (int soy = 0; soy < OLIVEC_AA_RES; ++soy) {
          // TODO: switch to 64 bits to make the overflow less likely
          // Also research the probability of overflow
          int res1 = (OLIVEC_AA_RES + 1);
          int dx = (x * res1 * 2 + 2 + sox * 2 - res1 * cx * 2 - res1);
          int dy = (y * res1 * 2 + 2 + soy * 2 - res1 * cy * 2 - res1);
          // Increments count by 1.
          if (dx * dx + dy * dy <= res1 * res1 * r * r * 2 * 2)
            count += 1;
        }
      }
      uint32_t alpha = ((color & 0xFF000000) >> (3 * 8)) * count /
                       OLIVEC_AA_RES / OLIVEC_AA_RES;
      uint32_t updated_color = (color & 0x00FFFFFF) | (alpha << (3 * 8));
      olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), updated_color);
    }
  }
}

// TODO: AA for line
// TODO: lines with different thiccness
/**
 * @brief Draw a line from x1 y1 to x2 y2. This is useful for drawing lines that
 * don't have a bounding box.
 * @param oc The canvas to draw on. This is modified by this function
 * @param x1 The x coordinate of the start of the line.
 * @param y1 The y coordinate of the start of the line.
 * @param x2 The x coordinate of the end of the line.
 * @param y2 The y coordinate of the end of the line.
 * @param color The color of the line to draw ( 0xRRGGBBAA
 */
void olivec_line(Olivec_Canvas oc, int x1, int y1, int x2, int y2,
                 uint32_t color) {
  int dx = x2 - x1;
  int dy = y2 - y1;

  // If both of the differences are 0 there will be a division by 0 below.
  // Set the color of the blending color
  if (dx == 0 && dy == 0) {
    // Set the color of the blending area
    if (0 <= x1 && x1 < (int)oc.width && 0 <= y1 && y1 < (int)oc.height) {
      olivec_blend_color(&OLIVEC_PIXEL(oc, x1, y1), color);
    }
    return;
  }

  // Draw a line of the line.
  if (OLIVEC_ABS(int, dx) > OLIVEC_ABS(int, dy)) {
    // x1 x2 and y1 y2
    if (x1 > x2) {
      OLIVEC_SWAP(int, x1, x2);
      OLIVEC_SWAP(int, y1, y2);
    }

    // Cull out invisible line
    // if x1 x1 oc. width
    if (x1 > (int)oc.width)
      return;
    // if x2 0 return false
    if (x2 < 0)
      return;

    // Clamp the line to the boundaries
    // Set x1 to 0 to 0
    if (x1 < 0)
      x1 = 0;
    // x2 x2 x2 1 if x2 x2 oc. width
    if (x2 >= (int)oc.width)
      x2 = (int)oc.width - 1;

    // Draw the line on the line
    for (int x = x1; x <= x2; ++x) {
      int y = dy * (x - x1) / dx + y1;
      // TODO: move boundary checks out side of the loops in olivec_draw_line
      // Set the color of the blending area
      if (0 <= y && y < (int)oc.height) {
        olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), color);
      }
    }
  } else {
    // Swaps the x and y values.
    if (y1 > y2) {
      OLIVEC_SWAP(int, x1, x2);
      OLIVEC_SWAP(int, y1, y2);
    }

    // Cull out invisible line
    // Returns true if y1 is greater than the height of the image
    if (y1 > (int)oc.height)
      return;
    // Returns true if y2 is negative.
    if (y2 < 0)
      return;

    // Clamp the line to the boundaries
    // Set y1 to 0 to the bottom of the y axis.
    if (y1 < 0)
      y1 = 0;
    // Y coordinate of the last item in the image.
    if (y2 >= (int)oc.height)
      y2 = (int)oc.height - 1;

    // Draw the line on the line.
    for (int y = y1; y <= y2; ++y) {
      int x = dx * (y - y1) / dy + x1;
      // TODO: move boundary checks out side of the loops in olivec_draw_line
      // Set the color of the blending area
      if (0 <= x && x < (int)oc.width) {
        olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), color);
      }
    }
  }
}

// TODO: AA for triangle
/**
 * @brief Draw a triangle. This is equivalent to drawing a barycentric
 * triangular mesh on the Olivec_Canvas.
 * @param oc The canvas on which to draw the triangle.
 * @param x1 The x coordinate of the first point of the triangle.
 * @param y1 The y coordinate of the first point of the triangle.
 * @param x2 The x coordinate of the second point of the triangle.
 * @param y2 The y coordinate of the second point of the triangle.
 * @param x3 The x coordinate of the third point of the triangle.
 * @param y3 The y coordinate of the third point of the triangle.
 * @param color The color of the triangle in the format 0xRRGGBB
 */
void olivec_triangle(Olivec_Canvas oc, int x1, int y1, int x2, int y2, int x3,
                     int y3, uint32_t color) {
  int lx, hx, ly, hy;
  // Normalize triangles and barycentric triangles.
  if (olivec_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
                                &lx, &hx, &ly, &hy)) {
    // Draw the blending color of the barycentric area.
    for (int y = ly; y <= hy; ++y) {
      // blend color of the barycentric plane
      for (int x = lx; x <= hx; ++x) {
        int u1, u2, det;
        // blend color of the barycentric plane
        if (olivec_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
          olivec_blend_color(&OLIVEC_PIXEL(oc, x, y), color);
        }
      }
    }
  }
}
