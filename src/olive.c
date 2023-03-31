#include "olive/base/figure.h"
#include "olive/types.h"
#include "olive/utils/math.h"
#include <math.h>
#include <stdint.h>

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
