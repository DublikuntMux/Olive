#ifndef OLIVE_SPRITE_H
#define OLIVE_SPRITE_H

#include "olive/types.h"
#include <stdint.h>

void olive_sprite_blend(Olive_Canvas oc, int x, int y, int w, int h,
		Olive_Canvas sprite);

void olive_sprite_copy(Olive_Canvas oc, int x, int y, int w, int h,
		Olive_Canvas sprite);

uint32_t olive_pixel_bilinear(Olive_Canvas sprite, int nx, int ny, int w,
		int h);

void olive_sprite_copy_bilinear(Olive_Canvas oc, int x, int y, int w, int h,
		Olive_Canvas sprite);

#endif // OLIVE_SPRITE_H
