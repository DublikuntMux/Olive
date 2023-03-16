#include "./assets/Lena_112.h"
#include "helpers/vc.c"
#include <math.h>
#include <olive/olive.h>

#define WIDTH 960
#define HEIGHT 720

static uint32_t dst[WIDTH * HEIGHT];
static float global_time = 0;

#define SRC_SCALE 3

Olive_Canvas vc_render(float dt) {
	global_time += dt;

	float t = sinf(10 * global_time);

	Olive_Canvas dst_canvas = olive_canvas(dst, WIDTH, HEIGHT, WIDTH);

	olive_fill(dst_canvas, 0xFF181818);

	float factor = 100.0f;
	int w = Lena_112_width * SRC_SCALE - t * factor;
	int h = Lena_112_height * SRC_SCALE + t * factor;

	olive_sprite_copy_bilinear(dst_canvas, WIDTH / 2 - w / 2, HEIGHT - h, w, h,
			olive_canvas(Lena_112_pixels, Lena_112_width,
					Lena_112_height, Lena_112_width));

	return dst_canvas;
}
