#ifndef OLIVE_H
#define OLIVE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef OLIVECDEF
#define OLIVECDEF static inline
#endif

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

#include "font.h"

#define OLIVEC_CANVAS_NULL ((Olivec_Canvas){0})
#define OLIVEC_PIXEL(oc, x, y) (oc).pixels[(y) * (oc).stride + (x)]

OLIVECDEF Olivec_Canvas olivec_canvas(uint32_t *pixels, size_t width,
                                      size_t height, size_t stride);
OLIVECDEF Olivec_Canvas olivec_subcanvas(Olivec_Canvas oc, int x, int y, int w,
                                         int h);
OLIVECDEF void olivec_blend_color(uint32_t *c1, uint32_t c2);
OLIVECDEF void olivec_fill(Olivec_Canvas oc, uint32_t color);
OLIVECDEF void olivec_rect(Olivec_Canvas oc, int x, int y, int w, int h,
                           uint32_t color);
OLIVECDEF void olivec_frame(Olivec_Canvas oc, int x, int y, int w, int h,
                            size_t thiccness, uint32_t color);
OLIVECDEF void olivec_circle(Olivec_Canvas oc, int cx, int cy, int r,
                             uint32_t color);
OLIVECDEF void olivec_ellipse(Olivec_Canvas oc, int cx, int cy, int rx, int ry,
                              uint32_t color);
// TODO: lines with different thiccness
OLIVECDEF void olivec_line(Olivec_Canvas oc, int x1, int y1, int x2, int y2,
                           uint32_t color);
OLIVECDEF bool olivec_normalize_triangle(size_t width, size_t height, int x1,
                                         int y1, int x2, int y2, int x3, int y3,
                                         int *lx, int *hx, int *ly, int *hy);
OLIVECDEF bool olivec_barycentric(int x1, int y1, int x2, int y2, int x3,
                                  int y3, int xp, int yp, int *u1, int *u2,
                                  int *det);
OLIVECDEF void olivec_triangle(Olivec_Canvas oc, int x1, int y1, int x2, int y2,
                               int x3, int y3, uint32_t color);
OLIVECDEF void olivec_triangle3c(Olivec_Canvas oc, int x1, int y1, int x2,
                                 int y2, int x3, int y3, uint32_t c1,
                                 uint32_t c2, uint32_t c3);
OLIVECDEF void olivec_triangle3z(Olivec_Canvas oc, int x1, int y1, int x2,
                                 int y2, int x3, int y3, float z1, float z2,
                                 float z3);
OLIVECDEF void olivec_triangle3uv(Olivec_Canvas oc, int x1, int y1, int x2,
                                  int y2, int x3, int y3, float tx1, float ty1,
                                  float tx2, float ty2, float tx3, float ty3,
                                  float z1, float z2, float z3,
                                  Olivec_Canvas texture);
OLIVECDEF void olivec_triangle3uv_bilinear(Olivec_Canvas oc, int x1, int y1,
                                           int x2, int y2, int x3, int y3,
                                           float tx1, float ty1, float tx2,
                                           float ty2, float tx3, float ty3,
                                           float z1, float z2, float z3,
                                           Olivec_Canvas texture);
OLIVECDEF void olivec_text(Olivec_Canvas oc, const char *text, int x, int y,
                           Olivec_Font font, size_t size, uint32_t color);
OLIVECDEF void olivec_sprite_blend(Olivec_Canvas oc, int x, int y, int w, int h,
                                   Olivec_Canvas sprite);
OLIVECDEF void olivec_sprite_copy(Olivec_Canvas oc, int x, int y, int w, int h,
                                  Olivec_Canvas sprite);
OLIVECDEF void olivec_sprite_copy_bilinear(Olivec_Canvas oc, int x, int y,
                                           int w, int h, Olivec_Canvas sprite);
OLIVECDEF uint32_t olivec_pixel_bilinear(Olivec_Canvas sprite, int nx, int ny,
                                         int w, int h);

typedef struct {
  // Safe ranges to iterate over.
  int x1, x2;
  int y1, y2;

  // Original uncut ranges some parts of which may be outside of the canvas
  // boundaries.
  int ox1, ox2;
  int oy1, oy2;
} Olivec_Normalized_Rect;

// The point of this function is to produce two ranges x1..x2 and y1..y2 that
// are guaranteed to be safe to iterate over the canvas of size pixels_width by
// pixels_height without any boundary checks.
//
// Olivec_Normalized_Rect nr = {0};
// if (olivec_normalize_rect(x, y, w, h, WIDTH, HEIGHT, &nr)) {
//     for (int x = nr.x1; x <= nr.x2; ++x) {
//         for (int y = nr.y1; y <= nr.y2; ++y) {
//             OLIVEC_PIXEL(oc, x, y) = 0x69696969;
//         }
//     }
// } else {
//     // Rectangle is invisible cause it's completely out-of-bounds
// }
OLIVECDEF bool olivec_normalize_rect(int x, int y, int w, int h,
                                     size_t canvas_width, size_t canvas_height,
                                     Olivec_Normalized_Rect *nr);

#endif // OLIVE_H
