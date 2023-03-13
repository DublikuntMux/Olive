#ifndef OLIVE_SPRITE_H
#define OLIVE_SPRITE_H

#include "olive/olive.h"
#include <stdint.h>

void olivec_sprite_blend(Olivec_Canvas oc, int x, int y, int w, int h,
                         Olivec_Canvas sprite);
void olivec_sprite_copy(Olivec_Canvas oc, int x, int y, int w, int h,
                        Olivec_Canvas sprite);
uint32_t olivec_pixel_bilinear(Olivec_Canvas sprite, int nx, int ny, int w,
                               int h);
void olivec_sprite_copy_bilinear(Olivec_Canvas oc, int x, int y, int w, int h,
                                 Olivec_Canvas sprite);

#endif // OLIVE_SPRITE_H
