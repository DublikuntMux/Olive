#ifndef OLIVE_COLOR_H
#define OLIVE_COLOR_H

#include "olive/types.h"
#include <stdint.h>

// TODO: custom pixel formats
// Maybe we can store pixel format info in Olive_Canvas
#define OLIVE_RED(color) (((color)&0x000000FF) >> (8 * 0))
#define OLIVE_GREEN(color) (((color)&0x0000FF00) >> (8 * 1))
#define OLIVE_BLUE(color) (((color)&0x00FF0000) >> (8 * 2))
#define OLIVE_ALPHA(color) (((color)&0xFF000000) >> (8 * 3))
#define OLIVE_RGBA(r, g, b, a)                           \
	((((r)&0xFF) << (8 * 0)) | (((g)&0xFF) << (8 * 1)) | \
			(((b)&0xFF) << (8 * 2)) | (((a)&0xFF) << (8 * 3)))

void olive_blend_color(uint32_t *c1, uint32_t c2);

void olive_fill(Olive_Canvas oc, uint32_t color);

uint32_t olive_mix_colors2(uint32_t c1, uint32_t c2, int u1, int det);

uint32_t olive_mix_colors3(uint32_t c1, uint32_t c2, uint32_t c3, int u1, int u2,
		int det);

#endif // OLIVE_COLOR_H
