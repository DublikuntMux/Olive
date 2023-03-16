#ifndef OLIVE_FIGURE_H
#define OLIVE_FIGURE_H

#include "olive/types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef OLIVE_AA_RES
#define OLIVE_AA_RES 2
#endif

void olive_rect(Olive_Canvas oc, int x, int y, int w, int h, uint32_t color);

bool olive_normalize_rect(int x, int y, int w, int h, size_t canvas_width,
		size_t canvas_height, Olive_Normalized_Rect *nr);

void olive_frame(Olive_Canvas oc, int x, int y, int w, int h, size_t t,
		uint32_t color);

void olive_ellipse(Olive_Canvas oc, int cx, int cy, int rx, int ry,
		uint32_t color);

void olive_circle(Olive_Canvas oc, int cx, int cy, int r, uint32_t color);

void olive_line(Olive_Canvas oc, int x1, int y1, int x2, int y2,
		uint32_t color);

void olive_triangle(Olive_Canvas oc, int x1, int y1, int x2, int y2, int x3,
		int y3, uint32_t color);

#endif // OLIVE_FIGURE_H
