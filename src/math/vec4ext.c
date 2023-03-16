#include "olive/math/vec3ext.h"
#include "olive/types.h"
#include "olive/utils/math.h"
#include <math.h>
#include <stdbool.h>

void olive_vec4_broadcast(float val, vec4 d) {
	d[0] = d[1] = d[2] = d[3] = val;
}

void olive_vec4_fill(vec4 v, float val) { v[0] = v[1] = v[2] = v[3] = val; }

bool olive_vec4_eq(vec4 v, float val) {
	return v[0] == val && v[0] == v[1] && v[0] == v[2] && v[0] == v[3];
}

bool olive_vec4_eq_eps(vec4 v, float val) {
	return fabsf(v[0] - val) <= FLT_EPSILON && fabsf(v[1] - val) <= FLT_EPSILON &&
			fabsf(v[2] - val) <= FLT_EPSILON && fabsf(v[3] - val) <= FLT_EPSILON;
}

bool olive_vec4_eq_all(vec4 v) { return olive_vec4_eq_eps(v, v[0]); }

bool olive_vec4_eqv(vec4 a, vec4 b) {
	return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

bool olive_vec4_eqv_eps(vec4 a, vec4 b) {
	return fabsf(a[0] - b[0]) <= FLT_EPSILON &&
			fabsf(a[1] - b[1]) <= FLT_EPSILON &&
			fabsf(a[2] - b[2]) <= FLT_EPSILON && fabsf(a[3] - b[3]) <= FLT_EPSILON;
}

float olive_vec4_max(vec4 v) {
	float max;

	max = olive_vec3_max(v);
	if (v[3] > max) {
		max = v[3];
}

	return max;
}

float olive_vec4_min(vec4 v) {
	float min;

	min = olive_vec3_min(v);
	if (v[3] < min) {
		min = v[3];
}

	return min;
}

bool olive_vec4_isnan(vec4 v) {
	return isnan(v[0]) || isnan(v[1]) || isnan(v[2]) || isnan(v[3]);
}

bool olive_vec4_isinf(vec4 v) {
	return isinf(v[0]) || isinf(v[1]) || isinf(v[2]) || isinf(v[3]);
}

bool olive_vec4_isvalid(vec4 v) {
	return !olive_vec4_isnan(v) && !olive_vec4_isinf(v);
}

void olive_vec4_sign(vec4 v, vec4 dest) {
	dest[0] = olive_signf(v[0]);
	dest[1] = olive_signf(v[1]);
	dest[2] = olive_signf(v[2]);
	dest[3] = olive_signf(v[3]);
}

void olive_vec4_abs(vec4 v, vec4 dest) {
	dest[0] = fabsf(v[0]);
	dest[1] = fabsf(v[1]);
	dest[2] = fabsf(v[2]);
	dest[3] = fabsf(v[3]);
}

void olive_vec4_fract(vec4 v, vec4 dest) {
	dest[0] = fminf(v[0] - floorf(v[0]), 0.999999940395355224609375f);
	dest[1] = fminf(v[1] - floorf(v[1]), 0.999999940395355224609375f);
	dest[2] = fminf(v[2] - floorf(v[2]), 0.999999940395355224609375f);
	dest[3] = fminf(v[3] - floorf(v[3]), 0.999999940395355224609375f);
}

float olive_vec4_hadd(vec4 v) { return v[0] + v[1] + v[2] + v[3]; }

void olive_vec4_sqrt(vec4 v, vec4 dest) {
	dest[0] = sqrtf(v[0]);
	dest[1] = sqrtf(v[1]);
	dest[2] = sqrtf(v[2]);
	dest[3] = sqrtf(v[3]);
}
