#include "olive/math/vec2ext.h"
#include "olive/types.h"
#include "olive/utils/math.h"
#include <math.h>

void olive_vec2(vec3 v3, vec2 dest) {
	dest[0] = v3[0];
	dest[1] = v3[1];
}

void olive_project_3d_2d(vec3 v3, vec2 dest) {
	if (v3[2] < 0) {
		v3[2] = -v3[2];
}
	if (v3[2] < 1e-6) {
		v3[2] += 1e-6;
}

	dest[0] = v3[0] / v3[2];
	dest[1] = v3[1] / v3[2];
}

void olive_vec2_copy(vec2 a, vec2 dest) {
	dest[0] = a[0];
	dest[1] = a[1];
}

void olive_vec2_zero(vec2 v) { v[0] = v[1] = 0.0f; }

void olive_vec2_one(vec2 v) { v[0] = v[1] = 1.0f; }

float olive_vec2_dot(vec2 a, vec2 b) { return a[0] * b[0] + a[1] * b[1]; }

float olive_vec2_cross(vec2 a, vec2 b) { return a[0] * b[1] - a[1] * b[0]; }

float olive_vec2_norm2(vec2 v) { return olive_vec2_dot(v, v); }

float olive_vec2_norm(vec2 vec) { return sqrtf(olive_vec2_norm2(vec)); }

void olive_vec2_add(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
}

void olive_vec2_adds(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
}

void olive_vec2_sub(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
}

void olive_vec2_subs(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
}

void olive_vec2_mul(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
}

void olive_vec2_scale(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
}

void olive_vec2_scale_as(vec2 v, float s, vec2 dest) {
	float norm;
	norm = olive_vec2_norm(v);

	if (norm == 0.0f) {
		olive_vec2_zero(dest);
		return;
	}

	olive_vec2_scale(v, s / norm, dest);
}

void olive_vec2_div(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] / b[0];
	dest[1] = a[1] / b[1];
}

void olive_vec2_divs(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] / s;
	dest[1] = v[1] / s;
}

void olive_vec2_addadd(vec2 a, vec2 b, vec2 dest) {
	dest[0] += a[0] + b[0];
	dest[1] += a[1] + b[1];
}

void olive_vec2_subadd(vec2 a, vec2 b, vec2 dest) {
	dest[0] += a[0] - b[0];
	dest[1] += a[1] - b[1];
}

void olive_vec2_muladd(vec2 a, vec2 b, vec2 dest) {
	dest[0] += a[0] * b[0];
	dest[1] += a[1] * b[1];
}

void olive_vec2_muladds(vec2 a, float s, vec2 dest) {
	dest[0] += a[0] * s;
	dest[1] += a[1] * s;
}

void olive_vec2_maxadd(vec2 a, vec2 b, vec2 dest) {
	dest[0] += olive_max(a[0], b[0]);
	dest[1] += olive_max(a[1], b[1]);
}

void olive_vec2_minadd(vec2 a, vec2 b, vec2 dest) {
	dest[0] += olive_min(a[0], b[0]);
	dest[1] += olive_min(a[1], b[1]);
}

void olive_vec2_negate_to(vec2 v, vec2 dest) {
	dest[0] = -v[0];
	dest[1] = -v[1];
}

void olive_vec2_negate(vec2 v) { olive_vec2_negate_to(v, v); }

void olive_vec2_normalize(vec2 v) {
	float norm;

	norm = olive_vec2_norm(v);

	if (norm == 0.0f) {
		v[0] = v[1] = 0.0f;
		return;
	}

	olive_vec2_scale(v, 1.0f / norm, v);
}

void olive_vec2_normalize_to(vec2 v, vec2 dest) {
	float norm;

	norm = olive_vec2_norm(v);

	if (norm == 0.0f) {
		olive_vec2_zero(dest);
		return;
	}

	olive_vec2_scale(v, 1.0f / norm, dest);
}

void olive_vec2_rotate(vec2 v, float angle, vec2 dest) {
	float c, s, x1, y1;

	c = cosf(angle);
	s = sinf(angle);

	x1 = v[0];
	y1 = v[1];

	dest[0] = c * x1 - s * y1;
	dest[1] = s * x1 + c * y1;
}

float olive_vec2_distance2(vec2 a, vec2 b) {
	return olive_pow2(b[0] - a[0]) + olive_pow2(b[1] - a[1]);
}

float olive_vec2_distance(vec2 a, vec2 b) {
	return sqrtf(olive_vec2_distance2(a, b));
}

void olive_vec2_maxv(vec2 a, vec2 b, vec2 dest) {
	dest[0] = olive_max(a[0], b[0]);
	dest[1] = olive_max(a[1], b[1]);
}

void olive_vec2_minv(vec2 a, vec2 b, vec2 dest) {
	dest[0] = olive_min(a[0], b[0]);
	dest[1] = olive_min(a[1], b[1]);
}

void olive_vec2_clamp(vec2 v, float minval, float maxval) {
	v[0] = olive_clamp(v[0], minval, maxval);
	v[1] = olive_clamp(v[1], minval, maxval);
}

void olive_vec2_lerp(vec2 from, vec2 to, float t, vec2 dest) {
	vec2 s, v;
	olive_vec2_fill(s, olive_clamp_zo(t));
	olive_vec2_sub(to, from, v);
	olive_vec2_mul(s, v, v);
	olive_vec2_add(from, v, dest);
}
