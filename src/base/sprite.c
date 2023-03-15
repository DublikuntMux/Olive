#include "olive/base/color.h"
#include "olive/base/figure.h"
#include "olive/types.h"
#include <stdint.h>

void olivec_sprite_blend(Olivec_Canvas oc, int x, int y, int w, int h,
                         Olivec_Canvas sprite) {
  if (sprite.width == 0)
    return;
  if (sprite.height == 0)
    return;

  Olivec_Normalized_Rect nr = {0};
  // Normalize rectangle to the nearest rectangle.
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;

  int xa = nr.ox1;
  if (w < 0)
    xa = nr.ox2;
  int ya = nr.oy1;
  if (h < 0)
    ya = nr.oy2;
  for (int i = nr.y1; i <= nr.y2; ++i) {
    for (int ii = nr.x1; ii <= nr.x2; ++ii) {
      size_t nx = (ii - xa) * ((int)sprite.width) / w;
      size_t ny = (i - ya) * ((int)sprite.height) / h;
      olivec_blend_color(&OLIVEC_PIXEL(oc, ii, i),
                         OLIVEC_PIXEL(sprite, nx, ny));
    }
  }
}

void olivec_sprite_copy(Olivec_Canvas oc, int x, int y, int w, int h,
                        Olivec_Canvas sprite) {
  if (sprite.width == 0)
    return;
  if (sprite.height == 0)
    return;

  // TODO: consider introducing flip parameter instead of relying on negative
  Olivec_Normalized_Rect nr = {0};
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;

  int xa = nr.ox1;
  if (w < 0)
    xa = nr.ox2;
  int ya = nr.oy1;
  if (h < 0)
    ya = nr.oy2;
  for (int i = nr.y1; i <= nr.y2; ++i) {
    for (int ii = nr.x1; ii <= nr.x2; ++ii) {
      size_t nx = (ii - xa) * ((int)sprite.width) / w;
      size_t ny = (i - ya) * ((int)sprite.height) / h;
      OLIVEC_PIXEL(oc, ii, i) = OLIVEC_PIXEL(sprite, nx, ny);
    }
  }
}

// TODO: olivec_pixel_bilinear does not check for out-of-bounds
uint32_t olivec_pixel_bilinear(Olivec_Canvas sprite, int nx, int ny, int w,
                               int h) {
  int px = nx % w;
  int py = ny % h;

  int x1 = nx / w, x2 = nx / w;
  int y1 = ny / h, y2 = ny / h;

  if (px < w / 2) {
    px += w / 2;
    x1 -= 1;
    if (x1 < 0)
      x1 = 0;
  } else {
    px -= w / 2;
    x2 += 1;
    if ((size_t)x2 >= sprite.width)
      x2 = sprite.width - 1;
  }

  if (py < h / 2) {
    py += h / 2;
    y1 -= 1;
    if (y1 < 0)
      y1 = 0;
  } else {
    py -= h / 2;
    y2 += 1;
    if ((size_t)y2 >= sprite.height)
      y2 = sprite.height - 1;
  }

  return mix_colors2(mix_colors2(OLIVEC_PIXEL(sprite, x1, y1),
                                 OLIVEC_PIXEL(sprite, x2, y1), px, w),
                     mix_colors2(OLIVEC_PIXEL(sprite, x1, y2),
                                 OLIVEC_PIXEL(sprite, x2, y2), px, w),
                     py, h);
}

void olivec_sprite_copy_bilinear(Olivec_Canvas oc, int x, int y, int w, int h,
                                 Olivec_Canvas sprite) {
  // TODO: support negative size in olivec_sprite_copy_bilinear()
  if (w <= 0)
    return;
  if (h <= 0)
    return;

  Olivec_Normalized_Rect nr = {0};
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return;

  for (int i = nr.y1; i <= nr.y2; ++i) {
    for (int ii = nr.x1; ii <= nr.x2; ++ii) {
      size_t nx = (ii - nr.ox1) * sprite.width;
      size_t ny = (i - nr.oy1) * sprite.height;
      OLIVEC_PIXEL(oc, ii, i) = olivec_pixel_bilinear(sprite, nx, ny, w, h);
    }
  }
}
