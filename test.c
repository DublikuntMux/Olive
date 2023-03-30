#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "./assets/testFont.h"
#include "./assets/tsodinCup.h"
#include "./assets/tsodinPog.h"
#include "olive/math/ivec2.h"
#include "olive/types.h"

#define return_defer(value) \
	do {                    \
		result = (value);   \
		goto defer;         \
	} while (0)
#define UNUSED(x) (void)(x)

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "olive/olive.h"

#define BACKGROUND_COLOR 0xFF202020
#define FOREGROUND_COLOR 0xFF2020FF
#define WHITE_COLOR 0xFFAAAAAA
#define RED_COLOR 0xFF2020AA
#define GREEN_COLOR 0xFF20AA20
#define BLUE_COLOR 0xFFAA2020
#define ERROR_COLOR 0xFFFF00FF

#define TEST_DIR_PATH "./test"

bool canvas_stbi_load(const char *file_path, Olive_Canvas *oc) {
	int width, height;
	uint32_t *pixels = (uint32_t *)stbi_load(file_path, &width, &height, NULL, 4);
	if (pixels == NULL) {
		return false;
	}
	*oc = olive_canvas(pixels, width, height, width);
	return true;
}

bool canvas_stbi_save(Olive_Canvas oc, const char *file_path) {
	return stbi_write_png(file_path, oc.width, oc.height, 4, oc.pixels,
			sizeof(uint32_t) * oc.stride);
}

typedef struct {
	Olive_Canvas (*generate_actual_canvas)(void);

	const char *id;
	const char *expected_file_path;
	const char *actual_file_path;
	const char *diff_file_path;
} Test_Case;

#define DEFINE_TEST_CASE(name)                                         \
	{                                                                  \
		.generate_actual_canvas = test_##name, .id = #name,            \
		.expected_file_path = TEST_DIR_PATH "/" #name "_expected.png", \
		.actual_file_path = TEST_DIR_PATH "/" #name "_actual.png",     \
		.diff_file_path = TEST_DIR_PATH "/" #name "_diff.png",         \
	}

bool update_test_case(const Test_Case *tc) {
	Olive_Canvas actual_canvas = tc->generate_actual_canvas();
	const char *expected_file_path = tc->expected_file_path;

	if (!canvas_stbi_save(actual_canvas, expected_file_path)) {
		fprintf(stderr, "ERROR: could not write file %s: %s\n", expected_file_path,
				strerror(errno));
		return (false);
	}
	printf("%s: Generated %s\n", tc->id, expected_file_path);
	return (true);
}

Olive_Canvas canvas_alloc(size_t width, size_t height) {
	uint32_t *pixels = malloc(sizeof(uint32_t) * width * height);
	return olive_canvas(pixels, width, height, width);
}

typedef enum {
	REPLAY_PASSED,
	REPLAY_FAILED,
	REPLAY_ERRORED,
} Replay_Result;

static inline size_t min_size(size_t a, size_t b) {
	if (a < b) {
		return a;
	}
	return b;
}

static inline size_t max_size(size_t a, size_t b) {
	if (a > b) {
		return a;
	}
	return b;
}

Replay_Result run_test_case(const char *program_path, const Test_Case *tc) {
	printf("%s:", tc->id);
	fflush(stdout);

	const char *expected_file_path = tc->expected_file_path;
	const char *actual_file_path = tc->actual_file_path;
	const char *diff_file_path = tc->diff_file_path;

	Olive_Canvas actual_canvas = tc->generate_actual_canvas();

	Olive_Canvas expected_canvas;
	if (!canvas_stbi_load(expected_file_path, &expected_canvas)) {
		fprintf(stderr, "\n");
		fprintf(stderr, "  ERROR: could not read %s: %s\n", expected_file_path,
				stbi_failure_reason());
		if (errno == ENOENT) {
			fprintf(stderr,
					"  HINT: Consider running `$ %s update %s` to create it\n",
					program_path, tc->id);
		}
		return (REPLAY_ERRORED);
	}

	bool failed = false;

	if (expected_canvas.width != actual_canvas.width ||
			expected_canvas.height != actual_canvas.height) {
		failed = true;
	}

	Olive_Canvas diff_canvas =
			canvas_alloc(max_size(expected_canvas.width, actual_canvas.width),
					max_size(expected_canvas.height, actual_canvas.height));
	olive_fill(diff_canvas, ERROR_COLOR);

	for (size_t y = 0; y < min_size(expected_canvas.height, actual_canvas.height);
			++y) {
		for (size_t x = 0; x < min_size(expected_canvas.width, actual_canvas.width);
				++x) {
			uint32_t expected_pixel = OLIVE_PIXEL(expected_canvas, x, y);
			uint32_t actual_pixel = OLIVE_PIXEL(actual_canvas, x, y);
			if (expected_pixel != actual_pixel) {
				OLIVE_PIXEL(diff_canvas, x, y) = ERROR_COLOR;
				failed = true;
			} else {
				OLIVE_PIXEL(diff_canvas, x, y) = expected_pixel;
			}
		}
	}

	if (failed) {
		fprintf(stderr, "\n");

		if (!canvas_stbi_save(actual_canvas, actual_file_path)) {
			fprintf(stderr,
					"  ERROR: could not write image file with actual pixels %s: %s\n",
					actual_file_path, strerror(errno));
			return (REPLAY_ERRORED);
		}

		if (!canvas_stbi_save(diff_canvas, diff_file_path)) {
			fprintf(stderr, "  ERROR: could not wrilte diff image file %s: %s\n",
					diff_file_path, strerror(errno));
			return (REPLAY_ERRORED);
		}

		fprintf(stderr, "  TEST FAILURE: unexpected pixels in generated image\n");
		fprintf(stderr, "    Expected: %s\n", expected_file_path);
		fprintf(stderr, "    Actual:   %s\n", actual_file_path);
		fprintf(stderr, "    Diff:     %s\n", diff_file_path);
		fprintf(stderr,
				"  HINT: If this behaviour is intentional confirm that by updating "
				"the image with `$ %s update`\n",
				program_path);
		return (REPLAY_FAILED);
	}

	printf(" OK\n");

	return (REPLAY_PASSED);
}

Olive_Canvas test_fill_rect(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);
	ivec2 pos = {width / 2 - width / 8, height / 2 - height / 8};
	olive_rect(oc, pos, width / 4, height / 4, RED_COLOR);
	pos[0] = width - 1;
	pos[1] = height - 1;
	olive_rect(oc, pos, -width / 2, -height / 2, GREEN_COLOR);
	pos[0] = -width / 4;
	pos[1] = -height / 4;
	olive_rect(oc, pos, width / 2, height / 2, BLUE_COLOR);
	return oc;
}

Olive_Canvas test_fill_circle(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);
	olive_circle(oc, IVEC2_ZERO, width / 2, RED_COLOR);
	ivec2 pos = {width / 2, height / 2};
	olive_circle(oc, pos, width / 4, BLUE_COLOR);
	pos[0] = width * 3 / 4;
	pos[1] = height * 3 / 4;
	olive_circle(oc, pos, -width / 4, GREEN_COLOR);
	return oc;
}

Olive_Canvas test_draw_line(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);
	olive_line(oc, 0, 0, width, height, RED_COLOR);
	olive_line(oc, width, 0, 0, height, BLUE_COLOR);
	olive_line(oc, width / 2, 0, width / 2, height, GREEN_COLOR);
	return oc;
}

Olive_Canvas test_fill_triangle(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas oc = canvas_alloc(width, height);

	olive_fill(oc, BACKGROUND_COLOR);

	{
		int x1 = width / 2, y1 = height / 8;
		int x2 = width / 8, y2 = height / 2;
		int x3 = width * 7 / 8, y3 = height * 7 / 8;
		olive_triangle(oc, x1, y1, x2, y2, x3, y3, RED_COLOR);
	}

	{
		int x1 = width / 2, y1 = height * 2 / 8;
		int x2 = width * 2 / 8, y2 = height / 2;
		int x3 = width * 6 / 8, y3 = height / 2;
		olive_triangle(oc, x1, y1, x2, y2, x3, y3, GREEN_COLOR);
	}

	{
		int x1 = width / 8, y1 = height / 8;
		int x2 = width / 8, y2 = height * 3 / 8;
		int x3 = width * 3 / 8, y3 = height * 3 / 8;
		olive_triangle(oc, x1, y1, x2, y2, x3, y3, BLUE_COLOR);
	}

	return oc;
}

Olive_Canvas test_alpha_blending(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);
	olive_rect(oc, IVEC2_ZERO, width * 3 / 4, height * 3 / 4, RED_COLOR);
	ivec2 pos = {width - 1, height - 1};
	olive_rect(oc, pos, -width * 3 / 4, -height * 3 / 4, 0x5520AA20);
	pos[0] = width / 2;
	pos[1] = height / 2;
	olive_circle(oc, pos, width / 4, 0xBBAA2020);
	olive_triangle(oc, 0, height - 1, width - 1, height - 1, width / 2, 0,
			0xBB20AAAA);
	olive_triangle3c(oc, 0, 0, width - 1, 0, width / 2, height - 1, 0xBB2020AA,
			0xBB20AA20, 0xBBAA2020);
	return oc;
}

Olive_Canvas test_checker_example(void) {
	int width = 800 / 2;
	int height = 600 / 2;
	int cols = (8 * 2);
	int rows = (6 * 2);
	int cell_width = (width / cols);
	int cell_height = (height / rows);
	Olive_Canvas oc = canvas_alloc(width, height);

	olive_fill(oc, BACKGROUND_COLOR);

	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			uint32_t color = BACKGROUND_COLOR;
			if ((x + y) % 2 == 0) {
				color = 0xFF2020FF;
			}
			ivec2 pos = {x * cell_width, y * cell_height};
			olive_rect(oc, pos, cell_width, cell_height, color);
		}
	}

	return oc;
}

Olive_Canvas test_circle_example(void) {
	int width = 800 / 2;
	int height = 600 / 2;
	int cols = (8 * 2);
	int rows = (6 * 2);
	int cell_width = (width / cols);
	int cell_height = (height / rows);
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);

	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			float u = (float)x / cols;
			float v = (float)y / rows;
			float t = (u + v) / 2;

			int radius = cell_width;
			if (cell_height < radius) {
				radius = cell_height;
			}
			ivec2 pos = {x * cell_width + cell_width / 2,
					y * cell_height + cell_height / 2};
			olive_circle(oc, pos,
					(size_t)(radius / 8 * (1 - t) + radius / 2 * t),
					FOREGROUND_COLOR);
		}
	}

	return oc;
}

Olive_Canvas test_lines_circle(void) {
	int width = 800 / 2;
	int height = 600 / 2;
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);

	size_t n = 20;
	float angle = 2 * PI / n;
	float length = width;
	if (length > height) {
		length = height;
	}
	length /= 3;
	float x1 = width / 2;
	float y1 = height / 2;
	for (size_t i = 0; i < n; ++i) {
		float x2 = x1 + cosf(angle * i) * length;
		float y2 = y1 + sinf(angle * i) * length;
		olive_line(oc, x1, y1, x2, y2, 0xFF1818FF);
	}

	return oc;
}

Olive_Canvas test_lines_example(void) {
	int width = 800 / 2;
	int height = 600 / 2;
	Olive_Canvas oc = canvas_alloc(width, height);

	olive_fill(oc, BACKGROUND_COLOR);
	olive_line(oc, 0, 0, width, height, FOREGROUND_COLOR);
	olive_line(oc, width, 0, 0, height, FOREGROUND_COLOR);
	olive_line(oc, 0, 0, width / 4, height, 0xFF20FF20);
	olive_line(oc, width / 4, 0, 0, height, 0xFF20FF20);
	olive_line(oc, width, 0, width / 4 * 3, height, 0xFF20FF20);
	olive_line(oc, width / 4 * 3, 0, width, height, 0xFF20FF20);
	olive_line(oc, 0, height / 2, width, height / 2, 0xFFFF3030);
	olive_line(oc, width / 2, 0, width / 2, height, 0xFFFF3030);

	return oc;
}

Olive_Canvas test_custom_font(void) {
	size_t size = 1;

	char *text = "the quick brown fox jumped over the lazy dog";
	size_t text_len = strlen(text);
	Olive_Canvas oc = canvas_alloc(1000, 300);
	olive_fill(oc, BACKGROUND_COLOR);
	olive_text(oc, text, oc.width / 2 - test_font.width * size * text_len / 2,
			oc.height / 4 - test_font.height * size / 2, test_font, size,
			FOREGROUND_COLOR);

	text = "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG";
	text_len = strlen(text);
	olive_text(oc, text, oc.width / 2 - test_font.width * size * text_len / 2,
			oc.height / 2 - test_font.height * size / 2, test_font, size,
			FOREGROUND_COLOR);

	text = "1234567890 !@#$%%&*(){}[]<>=\\|/,.;:?+-_";
	text_len = strlen(text);
	olive_text(oc, text, oc.width / 2 - test_font.width * size * text_len / 2,
			3 * oc.height / 4 - test_font.height * size / 2, test_font, size,
			FOREGROUND_COLOR);

	return oc;
}

Olive_Canvas test_hello_world_text_rendering(void) {
	size_t size = 5;
	const char *text = "hello, world";
	size_t text_len = strlen(text);
	Olive_Canvas oc = canvas_alloc(400, 150);
	olive_fill(oc, BACKGROUND_COLOR);
	olive_text(oc, text,
			oc.width / 2 - OLIVE_DEFAULT_FONT_WIDTH * size * text_len / 2,
			oc.height / 2 - OLIVE_DEFAULT_FONT_HEIGHT * size / 2,
			olive_default_font, size, FOREGROUND_COLOR);
	return oc;
}

Olive_Canvas test_line_edge_cases(void) {
	size_t width = 10;
	size_t height = 10;
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);
	// One pixel line
	olive_line(oc, width / 2, height / 2, width / 2, height / 2,
			FOREGROUND_COLOR);
	// Out-of-bounds horizontally
	olive_line(oc, width + 10, height / 2, width + 20, height / 2,
			FOREGROUND_COLOR);
	// Out-of-bounds vertically
	olive_line(oc, width / 2, height + 10, width / 2, height + 20,
			FOREGROUND_COLOR);
	return oc;
}

Olive_Canvas test_frame(void) {
	size_t width = 256;
	size_t height = 128;
	Olive_Canvas oc = canvas_alloc(width, height);
	olive_fill(oc, BACKGROUND_COLOR);

	{
		ivec2 epos = {width / 2, height / 2};
		olive_frame(oc, IVEC2_ZERO, epos, 1, RED_COLOR);
	}

	{
		ivec2 spos = {width / 2, height / 2};
		ivec2 epos = {width, height};
		olive_frame(oc, spos, epos, 1, GREEN_COLOR);
	}

	// Odd thiccness
	{
		size_t w = width / 2;
		size_t h = height / 2;
		size_t t = 5;
		ivec2 spos = {width / 2 - w / 2, height / 2 - h / 2};
		ivec2 epos = {w, h};
		olive_frame(oc, spos, epos, t, WHITE_COLOR);
		olive_frame(oc, spos, epos, 1, RED_COLOR);
	}

	// Even thiccness
	{
		size_t w = width / 4 + 1;
		size_t h = height / 4;
		size_t t = 6;
		ivec2 spos = {width / 2 - w / 2, height / 2 - h / 2};
		ivec2 epos = {w, h};
		olive_frame(oc, spos, epos, t, WHITE_COLOR);
		olive_frame(oc, spos, epos, 1, RED_COLOR);
	}

	// Zero thiccness
	{
		size_t w = width / 8;
		size_t h = height / 8;
		size_t t = 0;
		ivec2 spos = {width / 2 - w / 2, height / 2 - h / 2};
		ivec2 epos = {w, h};
		olive_frame(oc, spos, epos, t, WHITE_COLOR);
	}

	return oc;
}

Olive_Canvas test_sprite_blend(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas dst = canvas_alloc(width, height);
	olive_fill(dst, RED_COLOR);
	Olive_Canvas src = canvas_alloc(width, height);

	for (size_t y = 0; y < src.height; ++y) {
		for (size_t x = 0; x < src.width; ++x) {
			if ((x + y) % 2 == 0) {
				OLIVE_PIXEL(src, x, y) = 0;
			} else {
				OLIVE_PIXEL(src, x, y) = GREEN_COLOR;
			}
		}
	}

	olive_sprite_blend(dst, 0, 0, width, height, src);

	return dst;
}

Olive_Canvas test_sprite_blend_out_of_bounds_cut(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas dst = canvas_alloc(width, height);
	Olive_Canvas src = olive_canvas(tsodinPog_pixels, tsodinPog_width,
			tsodinPog_height, tsodinPog_width);
	olive_fill(dst, RED_COLOR);
	olive_sprite_blend(dst, -width / 2, -height / 2, width, height, src);
	olive_sprite_blend(dst, width / 2, -height / 2, width, height, src);
	olive_sprite_blend(dst, -width / 2, height / 2, width, height, src);
	olive_sprite_blend(dst, width / 2, height / 2, width, height, src);
	return dst;
}

Olive_Canvas test_sprite_blend_flip(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas dst = canvas_alloc(width, height);
	Olive_Canvas src = olive_canvas(tsodinPog_pixels, tsodinPog_width,
			tsodinPog_height, tsodinPog_width);
	olive_fill(dst, RED_COLOR);
	olive_sprite_blend(dst, 0, 0, width / 2, height / 2, src);
	olive_sprite_blend(dst, width - 1, 0, -width / 2, height / 2, src);
	olive_sprite_blend(dst, 0, height - 1, width / 2, -height / 2, src);
	olive_sprite_blend(dst, width - 1, height - 1, -width / 2, -height / 2, src);
	return dst;
}

Olive_Canvas test_sprite_blend_flip_cut(void) {
	size_t width = 128;
	size_t height = 128;
	Olive_Canvas dst = canvas_alloc(width, height);
	Olive_Canvas src = olive_canvas(tsodinPog_pixels, tsodinPog_width,
			tsodinPog_height, tsodinPog_width);
	olive_fill(dst, RED_COLOR);
	olive_sprite_blend(dst, -width / 2, -height / 2, width, height, src);
	olive_sprite_blend(dst, width - 1 + width / 2, -height / 2, -width, height,
			src);
	olive_sprite_blend(dst, -width / 2, height - 1 + height / 2, width, -height,
			src);
	olive_sprite_blend(dst, width - 1 + width / 2, height - 1 + height / 2,
			-width, -height, src);
	return dst;
}

Olive_Canvas test_empty_rect(void) {
	size_t w = 8;
	size_t h = 8;
	Olive_Canvas dst = canvas_alloc(w, h);
	olive_fill(dst, BACKGROUND_COLOR);
	ivec2 pos = {w / 2, h / 2};
	olive_rect(dst, pos, 0, 0, FOREGROUND_COLOR);
	return dst;
}

Olive_Canvas test_sprite_blend_empty_rect(void) {
	size_t w = 8;
	size_t h = 8;
	Olive_Canvas dst = canvas_alloc(w, h);
	Olive_Canvas src = olive_canvas(tsodinPog_pixels, tsodinPog_width,
			tsodinPog_height, tsodinPog_width);
	olive_fill(dst, BACKGROUND_COLOR);
	olive_sprite_blend(dst, 0, 0, 0, 0, src);
	return dst;
}

Olive_Canvas test_sprite_blend_null(void) {
	size_t w = 8;
	size_t h = 8;
	Olive_Canvas dst = canvas_alloc(w, h);
	olive_fill(dst, BACKGROUND_COLOR);
	olive_sprite_blend(dst, 0, 0, w, h, OLIVE_CANVAS_NULL);
	return dst;
}

Olive_Canvas test_sprite_blend_vs_copy(void) {
	Olive_Canvas tsodinCup = olive_canvas(tsodinCup_pixels, tsodinCup_width,
			tsodinCup_height, tsodinCup_width);
	size_t w = tsodinCup.width;
	size_t h = tsodinCup.height * 2;
	Olive_Canvas dst = canvas_alloc(w, h);
	olive_fill(dst, RED_COLOR);
	olive_sprite_blend(dst, 0, 0, tsodinCup.width, tsodinCup.height, tsodinCup);
	olive_sprite_copy(dst, 0, tsodinCup.height, tsodinCup.width,
			tsodinCup.height, tsodinCup);
	return dst;
}

Olive_Canvas test_barycentric_overflow(void) {
	size_t w = 256;
	size_t h = 256;
	Olive_Canvas dst = canvas_alloc(w, h);
	olive_fill(dst, 0xFF181818);
	olive_triangle3c(dst, w / 4, h / 4, w / 2, 0, 0, h, 0xFF0000FF, 0xFF00FF00,
			0xFFFF0000);
	return dst;
}

Olive_Canvas test_triangle_order_flip(void) {
	size_t w = 256;
	size_t h = 256;
	Olive_Canvas dst = canvas_alloc(w, h);
	olive_fill(dst, 0xFF181818);
	olive_triangle3c(dst, w / 4, h / 4, 0, h, w, 0, 0xFF00FF00, 0xFFFF0000,
			0xFF0000FF);
	return dst;
}

Olive_Canvas test_bilinear_interpolation(void) {
	size_t factor = 2;
	Olive_Canvas src = olive_canvas(tsodinPog_pixels, tsodinPog_width,
			tsodinPog_height, tsodinPog_width);
	Olive_Canvas dst = canvas_alloc(src.width * factor * 2, src.height * factor);
	olive_fill(dst, RED_COLOR);
	olive_sprite_copy(dst, 0, 0, src.width * factor, src.height * factor, src);
	olive_sprite_copy_bilinear(dst, src.width * factor, 0, src.width * factor,
			src.height * factor, src);
	return dst;
}

Olive_Canvas test_fill_ellipse(void) {
	size_t factor = 3;
	Olive_Canvas dst = canvas_alloc(100 * factor, 50 * factor);
	olive_fill(dst, BACKGROUND_COLOR);
	olive_ellipse(dst, dst.width / 2, dst.height / 2, dst.width / 3,
			dst.height / 3, RED_COLOR);
	return dst;
}

Test_Case test_cases[] = {
	DEFINE_TEST_CASE(fill_rect),
	DEFINE_TEST_CASE(fill_circle),
	DEFINE_TEST_CASE(draw_line),
	DEFINE_TEST_CASE(fill_triangle),
	DEFINE_TEST_CASE(alpha_blending),
	DEFINE_TEST_CASE(checker_example),
	DEFINE_TEST_CASE(circle_example),
	DEFINE_TEST_CASE(lines_example),
	DEFINE_TEST_CASE(hello_world_text_rendering),
	DEFINE_TEST_CASE(lines_circle),
	DEFINE_TEST_CASE(line_edge_cases),
	DEFINE_TEST_CASE(frame),
	DEFINE_TEST_CASE(sprite_blend),
	DEFINE_TEST_CASE(sprite_blend_out_of_bounds_cut),
	DEFINE_TEST_CASE(sprite_blend_flip),
	DEFINE_TEST_CASE(sprite_blend_flip_cut),
	DEFINE_TEST_CASE(sprite_blend_empty_rect),
	DEFINE_TEST_CASE(empty_rect),
	DEFINE_TEST_CASE(sprite_blend_null),
	DEFINE_TEST_CASE(sprite_blend_vs_copy),
	DEFINE_TEST_CASE(triangle_order_flip),
	DEFINE_TEST_CASE(barycentric_overflow),
	DEFINE_TEST_CASE(bilinear_interpolation),
	DEFINE_TEST_CASE(fill_ellipse),
	DEFINE_TEST_CASE(custom_font),
};
#define TEST_CASES_COUNT (sizeof(test_cases) / sizeof(test_cases[0]))

const char *shift(int *argc, char ***argv) {
	assert(*argc > 0);
	const char *result = *argv[0];
	*argc -= 1;
	*argv += 1;
	return result;
}

void list_available_tests(void) {
	fprintf(stderr, "Available tests:\n");
	for (size_t i = 0; i < TEST_CASES_COUNT; ++i) {
		fprintf(stderr, "    %s\n", test_cases[i].id);
	}
}

Test_Case *find_test_case_by_id(const char *id) {
	for (size_t i = 0; i < TEST_CASES_COUNT; ++i) {
		if (strcmp(test_cases[i].id, id) == 0) {
			return &test_cases[i];
		}
	}
	return NULL;
}

typedef struct {
	int (*run)(const char *program_path, int argc, char **argv);

	const char *id;
	const char *description;
} Subcmd;

void usage(const char *program_path);

int subcmd_run(const char *program_path, int argc, char **argv) {
	if (argc <= 0) {
		for (size_t i = 0; i < TEST_CASES_COUNT; ++i) {
			if (run_test_case(program_path, &test_cases[i]) == REPLAY_ERRORED) {
				return (1);
			}
		}
	} else {
		const char *test_case_id = shift(&argc, &argv);
		Test_Case *tc = find_test_case_by_id(test_case_id);
		if (tc == NULL) {
			list_available_tests();
			fprintf(stderr, "ERROR: could not find test case `%s`\n", test_case_id);
			return (1);
		}

		if (run_test_case(program_path, tc) == REPLAY_ERRORED) {
			return (1);
		}
	}

	return 0;
}

int subcmd_update(const char *program_path, int argc, char **argv) {
	UNUSED(program_path);

	if (argc <= 0) {
		for (size_t i = 0; i < TEST_CASES_COUNT; ++i) {
			if (!update_test_case(&test_cases[i])) {
				return (1);
			}
		}
	} else {
		const char *test_case_id = shift(&argc, &argv);
		Test_Case *tc = find_test_case_by_id(test_case_id);
		if (tc == NULL) {
			list_available_tests();
			fprintf(stderr, "ERROR: could not find test case `%s`\n", test_case_id);
			return (1);
		}

		if (!update_test_case(tc)) {
			return (1);
		}
	}

	return 0;
}

int subcmd_list(const char *program_path, int argc, char **argv) {
	UNUSED(program_path);
	UNUSED(argc);
	UNUSED(argv);
	list_available_tests();
	return 0;
}

int subcmd_help(const char *program_path, int argc, char **argv) {
	UNUSED(argc);
	UNUSED(argv);
	usage(program_path);
	return 0;
}

#define DEFINE_SUBCMD(name, desc) \
	{ .run = subcmd_##name, .id = #name, .description = desc, }

Subcmd subcmds[] = {
	DEFINE_SUBCMD(run, "Run the tests"),
	DEFINE_SUBCMD(update, "Update the tests"),
	DEFINE_SUBCMD(list, "List all available tests"),
	DEFINE_SUBCMD(help, "Print this help message"),
};
#define SUBCMDS_COUNT (sizeof(subcmds) / sizeof(subcmds[0]))

Subcmd *find_subcmd_by_id(const char *id) {
	for (size_t i = 0; i < SUBCMDS_COUNT; ++i) {
		if (strcmp(subcmds[i].id, id) == 0) {
			return &subcmds[i];
		}
	}
	return NULL;
}

void usage(const char *program_path) {
	fprintf(stderr, "Usage: %s [Subcommand]\n", program_path);
	fprintf(stderr, "Subcommands:\n");

	int width = 0;
	for (size_t i = 0; i < SUBCMDS_COUNT; ++i) {
		int len = strlen(subcmds[i].id);
		if (width < len) {
			width = len;
		}
	}

	for (size_t i = 0; i < SUBCMDS_COUNT; ++i) {
		fprintf(stderr, "    %-*s - %s\n", width, subcmds[i].id,
				subcmds[i].description);
	}
}

int main(int argc, char **argv) {
	int result = 0;

	{
		const char *program_path = shift(&argc, &argv);

		if (argc <= 0) {
			usage(program_path);
			fprintf(stderr, "ERROR: no subcommand is provided\n");
			return_defer(1);
		}

		const char *subcmd_id = shift(&argc, &argv);
		Subcmd *subcmd = find_subcmd_by_id(subcmd_id);
		if (subcmd != NULL) {
			return_defer(subcmd->run(program_path, argc, argv));
		} else {
			usage(program_path);
			fprintf(stderr, "ERROR: unknown subcommand `%s`\n", subcmd_id);
			return_defer(1);
		}
	}

defer:
	return result;
}
