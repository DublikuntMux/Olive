#include "olive/base/color.h"
#include <stdint.h>

void olive_blend_color(uint32_t *c1, uint32_t c2) {
	uint32_t r1 = OLIVE_RED(*c1);
	uint32_t g1 = OLIVE_GREEN(*c1);
	uint32_t b1 = OLIVE_BLUE(*c1);
	uint32_t a1 = OLIVE_ALPHA(*c1);

	uint32_t r2 = OLIVE_RED(c2);
	uint32_t g2 = OLIVE_GREEN(c2);
	uint32_t b2 = OLIVE_BLUE(c2);
	uint32_t a2 = OLIVE_ALPHA(c2);

	r1 = (r1 * (255 - a2) + r2 * a2) / 255;
	if (r1 > 255) {
		r1 = 255;
	}
	g1 = (g1 * (255 - a2) + g2 * a2) / 255;
	if (g1 > 255) {
		g1 = 255;
	}
	b1 = (b1 * (255 - a2) + b2 * a2) / 255;
	if (b1 > 255) {
		b1 = 255;
	}

	*c1 = OLIVE_RGBA(r1, g1, b1, a1);
}

void olive_fill(Olive_Canvas oc, uint32_t color) {
	for (size_t y = 0; y < oc.height; ++y) {
		for (size_t x = 0; x < oc.width; ++x) {
			OLIVE_PIXEL(oc, x, y) = color;
		}
	}
}

uint32_t olive_mix_colors2(uint32_t c1, uint32_t c2, int u1, int det) {
	// TODO: estimate how much overflows are an issue in integer only environment
	int64_t r1 = OLIVE_RED(c1);
	int64_t g1 = OLIVE_GREEN(c1);
	int64_t b1 = OLIVE_BLUE(c1);
	int64_t a1 = OLIVE_ALPHA(c1);

	int64_t r2 = OLIVE_RED(c2);
	int64_t g2 = OLIVE_GREEN(c2);
	int64_t b2 = OLIVE_BLUE(c2);
	int64_t a2 = OLIVE_ALPHA(c2);

	if (det != 0) {
		int u2 = det - u1;
		int64_t r4 = (r1 * u2 + r2 * u1) / det;
		int64_t g4 = (g1 * u2 + g2 * u1) / det;
		int64_t b4 = (b1 * u2 + b2 * u1) / det;
		int64_t a4 = (a1 * u2 + a2 * u1) / det;

		return OLIVE_RGBA(r4, g4, b4, a4);
	}

	return 0;
}

uint32_t olive_mix_colors3(uint32_t c1, uint32_t c2, uint32_t c3, int u1, int u2,
		int det) {
	// TODO: estimate how much overflows are an issue in integer only environment
	int64_t r1 = OLIVE_RED(c1);
	int64_t g1 = OLIVE_GREEN(c1);
	int64_t b1 = OLIVE_BLUE(c1);
	int64_t a1 = OLIVE_ALPHA(c1);

	int64_t r2 = OLIVE_RED(c2);
	int64_t g2 = OLIVE_GREEN(c2);
	int64_t b2 = OLIVE_BLUE(c2);
	int64_t a2 = OLIVE_ALPHA(c2);

	int64_t r3 = OLIVE_RED(c3);
	int64_t g3 = OLIVE_GREEN(c3);
	int64_t b3 = OLIVE_BLUE(c3);
	int64_t a3 = OLIVE_ALPHA(c3);

	if (det != 0) {
		int u3 = det - u1 - u2;
		int64_t r4 = (r1 * u1 + r2 * u2 + r3 * u3) / det;
		int64_t g4 = (g1 * u1 + g2 * u2 + g3 * u3) / det;
		int64_t b4 = (b1 * u1 + b2 * u2 + b3 * u3) / det;
		int64_t a4 = (a1 * u1 + a2 * u2 + a3 * u3) / det;

		return OLIVE_RGBA(r4, g4, b4, a4);
	}

	return 0;
}
