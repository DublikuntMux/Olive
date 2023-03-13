#ifndef OLIVE_TRINGLE_H
#define OLIVE_TRINGLE_H

#include "../olive.h"
#include <stdint.h>

bool olivec_normalize_triangle(size_t width, size_t height, int x1, int y1,
                               int x2, int y2, int x3, int y3, int *lx, int *hx,
                               int *ly, int *hy);
void olivec_triangle3c(Olivec_Canvas oc, int x1, int y1, int x2, int y2, int x3,
                       int y3, uint32_t c1, uint32_t c2, uint32_t c3);
void olivec_triangle3z(Olivec_Canvas oc, int x1, int y1, int x2, int y2, int x3,
                       int y3, float z1, float z2, float z3);
void olivec_triangle3uv(Olivec_Canvas oc, int x1, int y1, int x2, int y2,
                        int x3, int y3, float tx1, float ty1, float tx2,
                        float ty2, float tx3, float ty3, float z1, float z2,
                        float z3, Olivec_Canvas texture);
void olivec_triangle3uv_bilinear(Olivec_Canvas oc, int x1, int y1, int x2,
                                 int y2, int x3, int y3, float tx1, float ty1,
                                 float tx2, float ty2, float tx3, float ty3,
                                 float z1, float z2, float z3,
                                 Olivec_Canvas texture);

#endif // OLIVE_TRINGLE_H
