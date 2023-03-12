#include "olive.h"

#include "base/color.c"
#include "base/figure.c"
#include "base/sprite.c"
#include "base/tringle.c"

OLIVECDEF Olivec_Canvas olivec_canvas(uint32_t *pixels, size_t width,
                                      size_t height, size_t stride) {
  Olivec_Canvas oc = {
      .pixels = pixels,
      .width = width,
      .height = height,
      .stride = stride,
  };
  return oc;
}

OLIVECDEF Olivec_Canvas olivec_subcanvas(Olivec_Canvas oc, int x, int y, int w,
                                         int h) {
  Olivec_Normalized_Rect nr = {0};
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return OLIVEC_CANVAS_NULL;
  oc.pixels = &OLIVEC_PIXEL(oc, nr.x1, nr.y1);
  oc.width = nr.x2 - nr.x1 + 1;
  oc.height = nr.y2 - nr.y1 + 1;
  return oc;
}

OLIVECDEF bool olivec_barycentric(int x1, int y1, int x2, int y2, int x3,
                                  int y3, int xp, int yp, int *u1, int *u2,
                                  int *det) {
  *det = ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3));
  *u1 = ((y2 - y3) * (xp - x3) + (x3 - x2) * (yp - y3));
  *u2 = ((y3 - y1) * (xp - x3) + (x1 - x3) * (yp - y3));
  int u3 = *det - *u1 - *u2;
  return ((OLIVEC_SIGN(int, *u1) == OLIVEC_SIGN(int, *det) || *u1 == 0) &&
          (OLIVEC_SIGN(int, *u2) == OLIVEC_SIGN(int, *det) || *u2 == 0) &&
          (OLIVEC_SIGN(int, u3) == OLIVEC_SIGN(int, *det) || u3 == 0));
}

OLIVECDEF void olivec_text(Olivec_Canvas oc, const char *text, int tx, int ty,
                           Olivec_Font font, size_t glyph_size,
                           uint32_t color) {
  for (size_t i = 0; *text; ++i, ++text) {
    int gx = tx + i * font.width * glyph_size;
    int gy = ty;
    const char *glyph =
        &font.glyphs[(*text) * sizeof(char) * font.width * font.height];
    for (int dy = 0; (size_t)dy < font.height; ++dy) {
      for (int dx = 0; (size_t)dx < font.width; ++dx) {
        int px = gx + dx * glyph_size;
        int py = gy + dy * glyph_size;
        if (0 <= px && px < (int)oc.width && 0 <= py && py < (int)oc.height) {
          if (glyph[dy * font.width + dx]) {
            olivec_rect(oc, px, py, glyph_size, glyph_size, color);
          }
        }
      }
    }
  }
}

OLIVECDEF double olivec_binomial_coeffs(int n, int i) {
  double result = 1;
  for (int j = 1; j <= i; j++) {
    result *= (n - i + j) / (double)j;
  }
  return result;
}

// TODO: Benchmarking
// TODO: Bezier curves
// TODO: SIMD implementations
// TODO: olivec_ring
// TODO: fuzzer
// TODO: Stencil
