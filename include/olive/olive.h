#ifndef OLIVE_H
#define OLIVE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "types.h"

#include "olive/utils/math.h"

#include "math/ivec2.h"
#include "math/ivec3.h"
#include "math/ivec4.h"

#include "math/vec2.h"
#include "math/vec2ext.h"
#include "math/vec3.h"
#include "math/vec3ext.h"
#include "math/vec4.h"
#include "math/vec4ext.h"

#include "math/mat2.h"
#include "math/mat3.h"
#include "math/mat4.h"

#include "base/canvas.h"
#include "base/color.h"
#include "base/figure.h"
#include "base/sprite.h"
#include "base/tringle.h"

#include "font.h"

void olive_text(Olive_Canvas oc, const char *text, int tx, int ty,
		Olive_Font font, size_t glyph_size, uint32_t color);
double olive_binomial_coeffs(int n, int i);
void olive_bezier(Olive_Canvas oc, int degree, uint32_t color, int x1, int y1,
		int cx1, int cy1, int cx2, int cy2, int x2, int y2);

#endif // OLIVE_H
