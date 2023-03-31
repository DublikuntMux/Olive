#include "olive/base/canvas.h"
#include "olive/base/figure.h"
#include "olive/types.h"
#include <stdlib.h>

void olive_text(Olive_Canvas oc, const char *text, int tx, int ty, Olive_Font font, size_t glyph_size, uint32_t color) {
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
						ivec2 pos = { px, py };
						olive_rect(oc, pos, glyph_size, glyph_size, color);
					}
				}
			}
		}
	}
}

Olive_Font olive_loadfont_frombuff(unsigned char *buffer, int w, int h, int channels, int glyph_w, int glyph_h, char offset) {
	uint32_t *pixels = (uint32_t *)malloc(w * h * sizeof(uint32_t));
	for (int i = 0; i < w * h; i++) {
		pixels[i] = (uint32_t)buffer[i * channels];
	}

	Olive_Canvas atlas = olive_canvas(pixels, (size_t)w, (size_t)h, (size_t)w);
	size_t glyph_count = offset + ((w / glyph_w) * (h / glyph_h));
	size_t glyphs_per_row = w / glyph_w;
	unsigned char *glyphs = (unsigned char *)calloc(glyph_count * glyph_w * glyph_h, sizeof(unsigned char));

	for (size_t codepoint = 0; codepoint < glyph_count; ++codepoint) {
		int g_index = (unsigned char)codepoint - offset;
		int32_t g_x = (g_index % glyphs_per_row);
		int32_t g_y = (g_index - g_x) / glyphs_per_row;
		g_x *= glyph_w;
		g_y *= glyph_h;

		if (codepoint < (size_t)offset) {
			continue;
		}

		for (size_t py = 0; py < (size_t)glyph_h; ++py) {
			for (size_t px = 0; px < (size_t)glyph_w; ++px) {
				glyphs[codepoint * sizeof(unsigned char) * glyph_h * glyph_w + glyph_w * py + px] = OLIVE_PIXEL(atlas, g_x + px, g_y + py) == 0 ? 0 : 1;
			}
		}
	}

	free(pixels);
	Olive_Font font = {
		.width = (size_t)glyph_w,
		.height = (size_t)glyph_h,
		.glyphs = glyphs,
	};

	return font;
}

void olivec_loadfont_free(Olive_Font font) {
	free((void *)font.glyphs);
}
