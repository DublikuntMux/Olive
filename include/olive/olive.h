#ifndef OLIVE_H
#define OLIVE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef OLIVEC_AA_RES
#define OLIVEC_AA_RES 2
#endif

#define OLIVEC_SWAP(T, a, b)                                                   \
  do {                                                                         \
    T t = a;                                                                   \
    a = b;                                                                     \
    b = t;                                                                     \
  } while (0)
#define OLIVEC_SIGN(T, x) ((T)((x) > 0) - (T)((x) < 0))
#define OLIVEC_ABS(T, x) (OLIVEC_SIGN(T, x) * (x))
#define OLIVEC_CANVAS_NULL ((Olivec_Canvas){0})

typedef struct {
  size_t width, height;
  const char *glyphs;
} Olivec_Font;

typedef struct {
    uint32_t *pixels;
  size_t width;
  size_t height;
  size_t stride;
} Olivec_Canvas;

typedef struct {
  int x1, x2;
  int y1, y2;

  int ox1, ox2;
  int oy1, oy2;
} Olivec_Normalized_Rect;

#include "font.h"

#define OLIVEC_PIXEL(oc, x, y) (oc).pixels[(y) * (oc).stride + (x)]

Olivec_Canvas olivec_canvas(const uint32_t *pixels, size_t width, size_t height,
                            size_t stride);
Olivec_Canvas olivec_subcanvas(Olivec_Canvas oc, int x, int y, int w, int h);
bool olivec_barycentric(int x1, int y1, int x2, int y2, int x3, int y3, int xp,
                        int yp, int *u1, int *u2, int *det);
void olivec_text(Olivec_Canvas oc, const char *text, int tx, int ty,
                 Olivec_Font font, size_t glyph_size, uint32_t color);
double olivec_binomial_coeffs(int n, int i);

#endif // OLIVE_H
