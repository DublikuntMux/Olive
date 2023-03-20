#include "olive/base/figure.h"
#include "olive/base/color.h"
#include "olive/base/tringle.h"
#include "olive/math/ivec2.h"
#include "olive/types.h"
#include "olive/utils/math.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void olive_rect(Olive_Canvas oc, ivec2 pos, int w, int h, uint32_t color) {
	Olive_Normalized_Rect nr = { 0 };
	if (!olive_normalize_rect(pos, w, h, oc.width, oc.height, &nr)) {
		return;
	}
	for (int i = nr.start[0]; i <= nr.end[0]; ++i) {
		for (int ii = nr.start[1]; ii <= nr.end[1]; ++ii) {
			olive_blend_color(&OLIVE_PIXEL(oc, i, ii), color);
		}
	}
}

bool olive_normalize_rect(ivec2 pos, int w, int h, size_t canvas_width,
		size_t canvas_height, Olive_Normalized_Rect *nr) {
	if (w == 0) {
		return false;
	}
	if (h == 0) {
		return false;
	}

	olive_ivec2_copy(pos, nr->ostart);

	nr->oend[0] = nr->ostart[0] + olive_sign(w) * (abs(w) - 1);
	if (nr->ostart[0] > nr->oend[0]) {
		olive_swap(&nr->ostart[0], &nr->oend[0]);
	}
	nr->oend[1] = nr->ostart[1] + olive_sign(h) * (abs(h) - 1);
	if (nr->ostart[1] > nr->oend[1]) {
		olive_swap(&nr->ostart[1], &nr->oend[1]);
	}

	if (nr->ostart[0] >= (int)canvas_width) {
		return false;
	}
	if (nr->oend[0] < 0) {
		return false;
	}
	if (nr->ostart[1] >= (int)canvas_height) {
		return false;
	}
	if (nr->oend[1] < 0) {
		return false;
	}

	nr->start[0] = nr->ostart[0];
	nr->start[1] = nr->ostart[1];
	nr->end[0] = nr->oend[0];
	nr->end[1] = nr->oend[1];

	if (nr->start[0] < 0) {
		nr->start[0] = 0;
	}
	if (nr->end[0] >= (int)canvas_width) {
		nr->end[0] = (int)canvas_width - 1;
	}
	if (nr->start[1] < 0) {
		nr->start[1] = 0;
	}
	if (nr->end[1] >= (int)canvas_height) {
		nr->end[1] = (int)canvas_height - 1;
	}

	return true;
}

void olive_frame(Olive_Canvas oc, ivec2 spos, ivec2 epos, size_t t, uint32_t color) {
	if (t == 0) {
		return;
	}

	int x2 = spos[0] + olive_sign(epos[0]) * (abs(epos[0]) - 1);
	if (spos[0] > x2) {
		olive_swap(&spos[0], &x2);
	}
	int y2 = spos[1] + olive_sign(epos[1]) * (abs(epos[1]) - 1);
	if (spos[1] > y2) {
		olive_swap(&spos[1], &y2);
	}

	ivec2 pos = {spos[0] - t / 2, spos[1] - t / 2};
	olive_rect(oc, pos, (x2 - spos[0] + 1) + t / 2 * 2, t, color); // Top
	olive_rect(oc, pos, t, (y2 - spos[1] + 1) + t / 2 * 2, color); // Left

	pos[1] = y2 + t / 2;
	olive_rect(oc, pos, (x2 - spos[0] + 1) + t / 2 * 2, -t, color); // Bottom

	pos[0] = x2 + t / 2;
	pos[1] = spos[1] - t / 2;
	olive_rect(oc, pos, -t, (y2 - spos[1] + 1) + t / 2 * 2, color); // Right
}

void olive_ellipse(Olive_Canvas oc, int cx, int cy, int rx, int ry,
		uint32_t color) {
	Olive_Normalized_Rect nr = { 0 };
	int rx1 = rx + olive_sign(rx);
	int ry1 = ry + olive_sign(ry);
	ivec2 pos = { cx - rx1, cy - ry1 };
	if (!olive_normalize_rect(pos, 2 * rx1, 2 * ry1, oc.width,
				oc.height, &nr)) {
		return;
	}

	for (int y = nr.start[1]; y <= nr.end[1]; ++y) {
		for (int x = nr.start[0]; x <= nr.end[0]; ++x) {
			float nx = (x + 0.5 - nr.start[0]) / (2.0f * rx1);
			float ny = (y + 0.5 - nr.start[1]) / (2.0f * ry1);
			float dx = nx - 0.5;
			float dy = ny - 0.5;
			if (dx * dx + dy * dy <= 0.5 * 0.5) {
				OLIVE_PIXEL(oc, x, y) = color;
			}
		}
	}
}

void olive_circle(Olive_Canvas oc, ivec2 cpos, int r, uint32_t color) {
	Olive_Normalized_Rect nr = { 0 };
	int r1 = r + olive_sign(r);
	ivec2 pos = { cpos[0] - r1, cpos[1] - r1 };
	if (!olive_normalize_rect(pos, 2 * r1, 2 * r1, oc.width,
				oc.height, &nr)) {
		return;
	}

	for (int y = nr.start[1]; y <= nr.end[1]; ++y) {
		for (int x = nr.start[0]; x <= nr.end[0]; ++x) {
			int count = 0;
			for (int sox = 0; sox < OLIVE_AA_RES; ++sox) {
				for (int soy = 0; soy < OLIVE_AA_RES; ++soy) {
					int res1 = (OLIVE_AA_RES + 1);
					int dx = (x * res1 * 2 + 2 + sox * 2 - res1 * cpos[0] * 2 - res1);
					int dy = (y * res1 * 2 + 2 + soy * 2 - res1 * cpos[1] * 2 - res1);
					if (dx * dx + dy * dy <= res1 * res1 * r * r * 2 * 2) {
						count += 1;
					}
				}
			}
			uint32_t alpha = ((color & 0xFF000000) >> (3 * 8)) * count /
					OLIVE_AA_RES / OLIVE_AA_RES;
			uint32_t updated_color = (color & 0x00FFFFFF) | (alpha << (3 * 8));
			olive_blend_color(&OLIVE_PIXEL(oc, x, y), updated_color);
		}
	}
}

// TODO: AA for line
// TODO: lines with different thiccness
void olive_line(Olive_Canvas oc, int x1, int y1, int x2, int y2,
		uint32_t color) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx == 0 && dy == 0) {
		if (0 <= x1 && x1 < (int)oc.width && 0 <= y1 && y1 < (int)oc.height) {
			olive_blend_color(&OLIVE_PIXEL(oc, x1, y1), color);
		}
		return;
	}

	if (abs(dx) > abs(dy)) {
		if (x1 > x2) {
			olive_swap(&x1, &x2);
			olive_swap(&y1, &y2);
		}

		if (x1 > (int)oc.width) {
			return;
		}
		if (x2 < 0) {
			return;
		}
		if (x1 < 0) {
			x1 = 0;
		}
		if (x2 >= (int)oc.width) {
			x2 = (int)oc.width - 1;
		}

		for (int x = x1; x <= x2; ++x) {
			int y = dy * (x - x1) / dx + y1;
			if (0 <= y && y < (int)oc.height) {
				olive_blend_color(&OLIVE_PIXEL(oc, x, y), color);
			}
		}
	} else {
		if (y1 > y2) {
			olive_swap(&x1, &x2);
			olive_swap(&y1, &y2);
		}

		if (y1 > (int)oc.height) {
			return;
		}
		if (y2 < 0) {
			return;
		}
		if (y1 < 0) {
			y1 = 0;
		}
		if (y2 >= (int)oc.height) {
			y2 = (int)oc.height - 1;
		}

		for (int y = y1; y <= y2; ++y) {
			int x = dx * (y - y1) / dy + x1;
			if (0 <= x && x < (int)oc.width) {
				olive_blend_color(&OLIVE_PIXEL(oc, x, y), color);
			}
		}
	}
}

// TODO: AA for triangle
void olive_triangle(Olive_Canvas oc, int x1, int y1, int x2, int y2, int x3,
		int y3, uint32_t color) {
	int lx, hx, ly, hy;
	if (olive_normalize_triangle(oc.width, oc.height, x1, y1, x2, y2, x3, y3,
				&lx, &hx, &ly, &hy)) {
		for (int y = ly; y <= hy; ++y) {
			for (int x = lx; x <= hx; ++x) {
				int u1, u2, det;
				if (olive_barycentric(x1, y1, x2, y2, x3, y3, x, y, &u1, &u2, &det)) {
					olive_blend_color(&OLIVE_PIXEL(oc, x, y), color);
				}
			}
		}
	}
}
