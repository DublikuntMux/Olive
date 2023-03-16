#ifndef OLIVE_CANVAS_H
#define OLIVE_CANVAS_H

#include "olive/types.h"

Olive_Canvas olive_canvas(const uint32_t *pixels, size_t width, size_t height,
		size_t stride);

Olive_Canvas olive_subcanvas(Olive_Canvas oc, int x, int y, int w, int h);

#endif // OLIVE_CANVAS_H
