#include "olive/base/color.h"
#include "olive/base/figure.h"
#include "olive/types.h"
#include <stdint.h>

void olive_sprite_blend(Olive_Canvas oc, int x, int y, int w, int h,
		Olive_Canvas sprite) {
	if (sprite.width == 0) {
		return;
}
	if (sprite.height == 0) {
		return;
}

	Olive_Normalized_Rect nr = { 0 };
	// Normalize rectangle to the nearest rectangle.
	if (!olive_normalize_rect(x, y, w, h, oc.width, oc.height, &nr)) {
		return;
}

	int xa = nr.ostart[0];
	if (w < 0) {
		xa = nr.oend[0];
}
	int ya = nr.ostart[1];
	if (h < 0) {
		ya = nr.oend[1];
}
	for (int i = nr.start[1]; i <= nr.end[1]; ++i) {
		for (int ii = nr.start[0]; ii <= nr.end[0]; ++ii) {
			size_t nx = (ii - xa) * ((int)sprite.width) / w;
			size_t ny = (i - ya) * ((int)sprite.height) / h;
			olive_blend_color(&OLIVE_PIXEL(oc, ii, i),
					OLIVE_PIXEL(sprite, nx, ny));
		}
	}
}

void olive_sprite_copy(Olive_Canvas oc, int x, int y, int w, int h,
		Olive_Canvas sprite) {
	if (sprite.width == 0) {
		return;
}
	if (sprite.height == 0) {
		return;
}

	// TODO: consider introducing flip parameter instead of relying on negative
	Olive_Normalized_Rect nr = { 0 };
	if (!olive_normalize_rect(x, y, w, h, oc.width, oc.height, &nr)) {
		return;
}

	int xa = nr.ostart[0];
	if (w < 0) {
		xa = nr.oend[0];
}
	int ya = nr.ostart[1];
	if (h < 0) {
		ya = nr.oend[1];
}
	for (int i = nr.start[1]; i <= nr.end[1]; ++i) {
		for (int ii = nr.start[0]; ii <= nr.end[0]; ++ii) {
			size_t nx = (ii - xa) * ((int)sprite.width) / w;
			size_t ny = (i - ya) * ((int)sprite.height) / h;
			OLIVE_PIXEL(oc, ii, i) = OLIVE_PIXEL(sprite, nx, ny);
		}
	}
}

// TODO: olive_pixel_bilinear does not check for out-of-bounds
uint32_t olive_pixel_bilinear(Olive_Canvas sprite, int nx, int ny, int w,
		int h) {
	int px = nx % w;
	int py = ny % h;

	int x1 = nx / w, x2 = nx / w;
	int y1 = ny / h, y2 = ny / h;

	if (px < w / 2) {
		px += w / 2;
		x1 -= 1;
		if (x1 < 0) {
			x1 = 0;
}
	} else {
		px -= w / 2;
		x2 += 1;
		if ((size_t)x2 >= sprite.width) {
			x2 = sprite.width - 1;
}
	}

	if (py < h / 2) {
		py += h / 2;
		y1 -= 1;
		if (y1 < 0) {
			y1 = 0;
}
	} else {
		py -= h / 2;
		y2 += 1;
		if ((size_t)y2 >= sprite.height) {
			y2 = sprite.height - 1;
}
	}

	return olive_mix_colors2(olive_mix_colors2(OLIVE_PIXEL(sprite, x1, y1),
									 OLIVE_PIXEL(sprite, x2, y1), px, w),
			olive_mix_colors2(OLIVE_PIXEL(sprite, x1, y2),
					OLIVE_PIXEL(sprite, x2, y2), px, w),
			py, h);
}

void olive_sprite_copy_bilinear(Olive_Canvas oc, int x, int y, int w, int h,
		Olive_Canvas sprite) {
	// TODO: support negative size in olive_sprite_copy_bilinear()
	if (w <= 0) {
		return;
}
	if (h <= 0) {
		return;
}

	Olive_Normalized_Rect nr = { 0 };
	if (!olive_normalize_rect(x, y, w, h, oc.width, oc.height, &nr)) {
		return;
}

	for (int i = nr.start[1]; i <= nr.end[1]; ++i) {
		for (int ii = nr.start[0]; ii <= nr.end[0]; ++ii) {
			size_t nx = (ii - nr.ostart[0]) * sprite.width;
			size_t ny = (i - nr.ostart[1]) * sprite.height;
			OLIVE_PIXEL(oc, ii, i) = olive_pixel_bilinear(sprite, nx, ny, w, h);
		}
	}
}
