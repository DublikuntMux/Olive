#include "helpers/vc.c"
#include "olive/types.h"
#include <math.h>
#include <olive/olive.h>

#define WIDTH 960
#define HEIGHT 720
// #define WIDTH 1920
// #define HEIGHT 1080
#define BACKGROUND_COLOR 0xFF181818
#define CIRCLE_RADIUS 100
#define CIRCLE_COLOR 0x99AA2020

static uint32_t pixels[WIDTH * HEIGHT];
static float triangle_angle = 0;
static vec2 circle_pos = {WIDTH / 2.0f, HEIGHT / 2.0f};
static float circle_dx = 100;
static float circle_dy = 100;

static inline void rotate_point(float *x, float *y) {
	float dx = *x - WIDTH / 2.0f;
	float dy = *y - HEIGHT / 2.0f;
	float mag = sqrtf(dx * dx + dy * dy);
	float dir = atan2f(dy, dx) + triangle_angle;
	*x = cosf(dir) * mag + WIDTH / 2.0f;
	*y = sinf(dir) * mag + HEIGHT / 2.0f;
}

Olive_Canvas vc_render(float dt) {
	Olive_Canvas oc = olive_canvas(pixels, WIDTH, HEIGHT, WIDTH);

	olive_fill(oc, BACKGROUND_COLOR);

	// Triangle
	{
		triangle_angle += 0.5f * PI * dt;

		float x1 = WIDTH / 2.0f, y1 = HEIGHT / 8.0f;
		float x2 = WIDTH / 8.0f, y2 = HEIGHT / 2.0f;
		float x3 = WIDTH * 7.0f / 8.0f, y3 = HEIGHT * 7.0f / 8.0f;
		rotate_point(&x1, &y1);
		rotate_point(&x2, &y2);
		rotate_point(&x3, &y3);
		olive_triangle3c(oc, x1, y1, x2, y2, x3, y3, 0xFF2020FF, 0xFF20FF20,
				0xFFFF2020);
	}

	// Circle
	{
		float x = circle_pos[0] + circle_dx * dt;
		if (x - CIRCLE_RADIUS < 0 || x + CIRCLE_RADIUS >= WIDTH) {
			circle_dx *= -1;
		} else {
			circle_pos[0] = x;
		}

		float y = circle_pos[1] + circle_dy * dt;
		if (y - CIRCLE_RADIUS < 0 || y + CIRCLE_RADIUS >= HEIGHT) {
			circle_dy *= -1;
		} else {
			circle_pos[1] = y;
		}
		ivec2 cpos = {circle_pos[0], circle_pos[1]};
		olive_circle(oc, cpos, CIRCLE_RADIUS, CIRCLE_COLOR);
	}

	return oc;
}
