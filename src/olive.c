#include "olive/base/figure.h"
#include "olive/types.h"
#include "olive/utils/math.h"
#include <math.h>
#include <stdint.h>

void olive_text(Olive_Canvas oc, const char *text, int tx, int ty,
		Olive_Font font, size_t glyph_size, uint32_t color) {
	for (size_t i = 0; *text; ++i, ++text) {
		int gx = tx + i * font.width * glyph_size;
		int gy = ty;
		const unsigned char *glyph =
				&font.glyphs[(*text) * sizeof(char) * font.width * font.height];
		for (int dy = 0; (size_t)dy < font.height; ++dy) {
			for (int dx = 0; (size_t)dx < font.width; ++dx) {
				int px = gx + dx * glyph_size;
				int py = gy + dy * glyph_size;
				if (0 <= px && px < (int)oc.width && 0 <= py && py < (int)oc.height) {
					if (glyph[dy * font.width + dx]) {
						ivec2 pos = {px, py};
						olive_rect(oc, pos, glyph_size, glyph_size, color);
					}
				}
			}
		}
	}
}

double olive_binomial_coeffs(int n, int i) {
	double result = 1;
	for (int j = 1; j <= i; j++) {
		result *= (n - i + j) / (double)j;
	}
	return result;
}

void olive_bezier(Olive_Canvas oc, int degree, uint32_t color, int x1, int y1,
		int cx1, int cy1, int cx2, int cy2, int x2, int y2) {
	// TODO: Make the degree work for other than cubic.
	// TODO: test case for bezier curves

	int pointsx[4] = { x1, cx1, cx2, x2 };
	int pointsy[4] = { y1, cy1, cy2, y2 };

	// TODO: find a better iteration step size.
	double istep = 0.001;
	double scale_factor = istep;
	double x, y;

	while (scale_factor < 1) {
		x = 0, y = 0;
		for (int i = 0; i <= degree; i++) {
			double b = olive_binomial_coeffs(degree, i) *
					pow(1 - scale_factor, degree - i) * pow(scale_factor, i);
			x += b * (double)pointsx[i];
			y += b * (double)pointsy[i];
		}

		OLIVE_PIXEL(oc, (int)x, (int)y) = color;
		scale_factor += istep;
	}
}

// TODO: Benchmarking
// TODO: SIMD implementations
// TODO: olive_ring
// TODO: fuzzer
// TODO: Stencil
