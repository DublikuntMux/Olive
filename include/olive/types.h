#ifndef OLIVE_TYPES_H
#define OLIVE_TYPES_H

#include <stddef.h>
#include <stdint.h>

#define PI 3.1415926535897932384626433832795
#define PIf ((float)PI)
#define FLT_EPSILON 1e-5f

typedef struct {
  size_t width, height;
  const char *glyphs;
} Olivec_Font;

typedef struct {
  uint32_t *pixels;
  size_t width;
  size_t height;
  size_t stride;
} Olivec_Canvas;

typedef struct {
  int x1, x2;
  int y1, y2;

  int ox1, ox2;
  int oy1, oy2;
} Olivec_Normalized_Rect;

#define OLIVEC_PIXEL(oc, x, y) (oc).pixels[(y) * (oc).stride + (x)]
#define OLIVEC_CANVAS_NULL ((Olivec_Canvas){0})

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

#endif // OLIVE_TYPES_H
