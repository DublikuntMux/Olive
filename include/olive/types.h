#ifndef OLIVE_TYPES_H
#define OLIVE_TYPES_H

#include <stddef.h>
#include <stdint.h>

#define PI 3.1415926535897932384626433832795
#define PIf ((float)PI)
#define FLT_EPSILON 1e-5f

#define OLIVE_PIXEL(oc, x, y) (oc).pixels[(y) * (oc).stride + (x)]
#define OLIVE_CANVAS_NULL ((Olive_Canvas){ 0 })

typedef int ivec2[2];
typedef int ivec3[3];
typedef int ivec4[4];

typedef float vec2[2];
typedef float vec3[3];
typedef __attribute((aligned(16))) float vec4[4];

typedef vec4 versor;
typedef vec3 mat3[3];
typedef __attribute((aligned(16))) vec2 mat2[2];
typedef __attribute((aligned(16))) vec4 mat4[4];

typedef struct {
	size_t width, height;
	const char *glyphs;
} Olive_Font;

typedef struct {
	uint32_t *pixels;
	size_t width;
	size_t height;
	size_t stride;
} Olive_Canvas;

typedef struct {
	ivec2 start;
	ivec2 end;

	ivec2 ostart;
	ivec2 oend;
} Olive_Normalized_Rect;

#endif // OLIVE_TYPES_H
