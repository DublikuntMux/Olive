#include "assets/Lena_112.h"
#include "helpers/vc.c"
#include <math.h>
#include <olive/olive.h>

#define WIDTH 960
#define HEIGHT 720
#define BACKGROUND_COLOR 0xFF181818

static uint32_t pixels[WIDTH * HEIGHT];
static float triangle_angle = 0;

Olive_Canvas vc_render(float dt) {
	Olive_Canvas oc = olive_canvas(pixels, WIDTH, HEIGHT, WIDTH);
	Olive_Canvas Lena_112 = olive_canvas(Lena_112_pixels, Lena_112_width,
			Lena_112_height, Lena_112_width);

	olive_fill(oc, BACKGROUND_COLOR);

	{
		triangle_angle += 0.5f * PI * dt;

		float ps[4][2];
		float uvs[4][2] = {
			{ 0, 0 },
			{ 1, 0 },
			{ 1, 1 },
			{ 0, 1 },
		};
		float len = WIDTH / 4.0f;
		for (size_t i = 0; i < 4; ++i) {
			ps[i][0] = WIDTH / 2.0f + cosf(PI / 2 * i + triangle_angle) * len;
			ps[i][1] = HEIGHT / 2.0f + sinf(PI / 2 * i + triangle_angle) * len;
		}
		for (size_t i = 0; i < 2; ++i) {
			int i1 = (i * 2 + 0) % 4;
			int i2 = (i * 2 + 1) % 4;
			int i3 = (i * 2 + 2) % 4;
			olive_triangle3uv_bilinear(oc, ps[i1][0], ps[i1][1], ps[i2][0],
					ps[i2][1], ps[i3][0], ps[i3][1], uvs[i1][0],
					uvs[i1][1], uvs[i2][0], uvs[i2][1],
					uvs[i3][0], uvs[i3][1], 1, 1, 1, Lena_112);
		}
	}

	return oc;
}
