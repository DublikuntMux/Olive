#ifndef OLIVE_CANVAS_H
#define OLIVE_CANVAS_H

#include "olive/types.h"

Olivec_Canvas olivec_canvas(const uint32_t *pixels, size_t width, size_t height,
                            size_t stride);

Olivec_Canvas olivec_subcanvas(Olivec_Canvas oc, int x, int y, int w, int h);

#endif // OLIVE_CANVAS_H
