#ifndef OLIVE_FIGURE_H
#define OLIVE_FIGURE_H

#include "olive/olive.h"
#include <stdint.h>

void olivec_rect(Olivec_Canvas oc, int x, int y, int w, int h, uint32_t color);
bool olivec_normalize_rect(int x, int y, int w, int h, size_t canvas_width,
                           size_t canvas_height, Olivec_Normalized_Rect *nr);
void olivec_frame(Olivec_Canvas oc, int x, int y, int w, int h, size_t t,
                  uint32_t color);
void olivec_ellipse(Olivec_Canvas oc, int cx, int cy, int rx, int ry,
                    uint32_t color);
void olivec_circle(Olivec_Canvas oc, int cx, int cy, int r, uint32_t color);
void olivec_line(Olivec_Canvas oc, int x1, int y1, int x2, int y2,
                 uint32_t color);
void olivec_triangle(Olivec_Canvas oc, int x1, int y1, int x2, int y2, int x3,
                     int y3, uint32_t color);

#endif // OLIVE_FIGURE_H
