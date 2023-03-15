#include "olive/base/figure.h"
#include "olive/types.h"

Olivec_Canvas olivec_canvas(const uint32_t *pixels, size_t width, size_t height,
                            size_t stride) {
  Olivec_Canvas oc = {
      .pixels = pixels,
      .width = width,
      .height = height,
      .stride = stride,
  };
  return oc;
}

Olivec_Canvas olivec_subcanvas(Olivec_Canvas oc, int x, int y, int w, int h) {
  Olivec_Normalized_Rect nr = {0};
  if (!olivec_normalize_rect(x, y, w, h, oc.width, oc.height, &nr))
    return OLIVEC_CANVAS_NULL;
  oc.pixels = &OLIVEC_PIXEL(oc, nr.x1, nr.y1);
  oc.width = nr.x2 - nr.x1 + 1;
  oc.height = nr.y2 - nr.y1 + 1;
  return oc;
}
