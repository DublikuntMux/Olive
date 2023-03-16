#include "olive/base/figure.h"
#include "olive/types.h"

Olive_Canvas olive_canvas(const uint32_t *pixels, size_t width, size_t height,
		size_t stride) {
	Olive_Canvas oc = {
		.pixels = pixels,
		.width = width,
		.height = height,
		.stride = stride,
	};
	return oc;
}

Olive_Canvas olive_subcanvas(Olive_Canvas oc, int x, int y, int w, int h) {
	Olive_Normalized_Rect nr = { 0 };
	if (!olive_normalize_rect(x, y, w, h, oc.width, oc.height, &nr)) {
		return OLIVE_CANVAS_NULL;
	}
	oc.pixels = &OLIVE_PIXEL(oc, nr.start[0], nr.start[1]);
	oc.width = nr.end[0] - nr.start[0] + 1;
	oc.height = nr.end[1] - nr.start[1] + 1;
	return oc;
}
