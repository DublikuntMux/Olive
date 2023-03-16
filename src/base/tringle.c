#include "olive/base/color.h"
#include "olive/base/sprite.h"
#include "olive/types.h"
#include "olive/utils/math.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool olive_normalize_triangle(size_t width, size_t height, int x1, int y1,
		int x2, int y2, int x3, int y3, int *lx, int *hx,
		int *ly, int *hy) {
	*lx = x1;
	*hx = x1;

	if (*lx > x2) {
		*lx = x2;
	}
	if (*lx > x3) {
		*lx = x3;
	}
	if (*hx < x2) {
		*hx = x2;
	}
	if (*hx < x3) {
		*hx = x3;
	}
	if (*lx < 0) {
		*lx = 0;
	}
	if ((size_t)*lx >= width) {
		return false;
	};
	if (*hx < 0) {
		return false;
	};
	if ((size_t)*hx >= width) {
		*hx = width - 1;
	}

	*ly = y1;
	*hy = y1;
	if (*ly > y2) {
		*ly = y2;
	}
	if (*ly > y3) {
		*ly = y3;
	}
	if (*hy < y2) {
		*hy = y2;
	}
	if (*hy < y3) {
		*hy = y3;
	}
	if (*ly < 0) {
		*ly = 0;
	}

	if ((size_t)*ly >= height) {
		return false;
	};

	if (*hy < 0) {
		return false;
	};

	if ((size_t)*hy >= height) {
		*hy = height - 1;
	}

	return true;
}

void olive_triangle3c(Olive_Canvas oc, int x1, int y1, int x2, int y2, int x3,
		int y3, uint32_t c1, uint32_t c2, uint32_t c3) {
	int lx, hx, ly, hy;
	if (olive_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
				&lx, &hx, &ly, &hy)) {
		for (int y = ly; y <= hy; ++y) {
			for (int x = lx; x <= hx; ++x) {
				int u1, u2, det;
				if (olive_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
					olive_blend_color(&OLIVE_PIXEL(oc, x, y),
							olive_mix_colors3(c1, c2, c3, u1, u2, det));
				}
			}
		}
	}
}

void olive_triangle3z(Olive_Canvas oc, int x1, int y1, int x2, int y2, int x3,
		int y3, float z1, float z2, float z3) {
	int lx, hx, ly, hy;
	if (olive_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
				&lx, &hx, &ly, &hy)) {
		for (int y = ly; y <= hy; ++y) {
			for (int x = lx; x <= hx; ++x) {
				int u1, u2, det;
				if (olive_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
					float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
					OLIVE_PIXEL(oc, x, y) = *(uint32_t *)&z;
				}
			}
		}
	}
}

void olive_triangle3uv(Olive_Canvas oc, int x1, int y1, int x2, int y2,
		int x3, int y3, float tx1, float ty1, float tx2,
		float ty2, float tx3, float ty3, float z1, float z2,
		float z3, Olive_Canvas texture) {
	int lx, hx, ly, hy;

	if (olive_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
				&lx, &hx, &ly, &hy)) {
		for (int y = ly; y <= hy; ++y) {
			for (int x = lx; x <= hx; ++x) {
				int u1, u2, det;
				if (olive_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
					int u3 = det - u1 - u2;
					float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
					float tx = tx1 * u1 / det + tx2 * u2 / det + tx3 * u3 / det;
					float ty = ty1 * u1 / det + ty2 * u2 / det + ty3 * u3 / det;

					int texture_x = tx / z * texture.width;
					if (texture_x < 0) {
						texture_x = 0;
					}
					if ((size_t)texture_x >= texture.width) {
						texture_x = texture.width - 1;
					}

					int texture_y = ty / z * texture.height;
					if (texture_y < 0) {
						texture_y = 0;
					}
					if ((size_t)texture_y >= texture.height) {
						texture_y = texture.height - 1;
					}
					OLIVE_PIXEL(oc, x, y) =
							OLIVE_PIXEL(texture, (int)texture_x, (int)texture_y);
				}
			}
		}
	}
}

void olive_triangle3uv_bilinear(Olive_Canvas oc, int x1, int y1, int x2,
		int y2, int x3, int y3, float tx1, float ty1,
		float tx2, float ty2, float tx3, float ty3,
		float z1, float z2, float z3,
		Olive_Canvas texture) {
	int lx, hx, ly, hy;

	if (olive_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
				&lx, &hx, &ly, &hy)) {
		for (int y = ly; y <= hy; ++y) {
			for (int x = lx; x <= hx; ++x) {
				int u1, u2, det;
				if (olive_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
					int u3 = det - u1 - u2;
					float z = z1 * u1 / det + z2 * u2 / det + z3 * (det - u1 - u2) / det;
					float tx = tx1 * u1 / det + tx2 * u2 / det + tx3 * u3 / det;
					float ty = ty1 * u1 / det + ty2 * u2 / det + ty3 * u3 / det;

					float texture_x = tx / z * texture.width;
					if (texture_x < 0) {
						texture_x = 0;
					}
					if (texture_x >= (float)texture.width) {
						texture_x = texture.width - 1;
					}

					float texture_y = ty / z * texture.height;
					if (texture_y < 0) {
						texture_y = 0;
					}
					if (texture_y >= (float)texture.height) {
						texture_y = texture.height - 1;
					}

					int precision = 100;
					OLIVE_PIXEL(oc, x, y) = olive_pixel_bilinear(
							texture, texture_x * precision, texture_y * precision, precision,
							precision);
				}
			}
		}
	}
}
