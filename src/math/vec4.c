#include "olive/math/vec4ext.h"
#include "olive/types.h"
#include "olive/utils/math.h"
#include <math.h>

void olive_vec4(vec3 v3, float last, vec4 dest) {
	dest[0] = v3[0];
	dest[1] = v3[1];
	dest[2] = v3[2];
	dest[3] = last;
}

void olive_vec4_copy3(vec4 a, vec3 dest) {
	dest[0] = a[0];
	dest[1] = a[1];
	dest[2] = a[2];
}

void olive_vec4_copy(vec4 v, vec4 dest) {
	dest[0] = v[0];
	dest[1] = v[1];
	dest[2] = v[2];
	dest[3] = v[3];
}

void olive_vec4_ucopy(vec4 v, vec4 dest) {
	dest[0] = v[0];
	dest[1] = v[1];
	dest[2] = v[2];
	dest[3] = v[3];
}

void olive_vec4_zero(vec4 v) {
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
}

void olive_vec4_one(vec4 v) {
	v[0] = 1.0f;
	v[1] = 1.0f;
	v[2] = 1.0f;
	v[3] = 1.0f;
}

float olive_vec4_dot(vec4 a, vec4 b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

float olive_vec4_norm2(vec4 v) { return olive_vec4_dot(v, v); }

float olive_vec4_norm(vec4 v) { return sqrtf(olive_vec4_dot(v, v)); }

float olive_vec4_norm_one(vec4 v) {
	vec4 t;
	olive_vec4_abs(v, t);
	return olive_vec4_hadd(t);
}

float olive_vec4_norm_inf(vec4 v) {
	vec4 t;
	olive_vec4_abs(v, t);
	return olive_vec4_max(t);
}

void olive_vec4_add(vec4 a, vec4 b, vec4 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
	dest[3] = a[3] + b[3];
}

void olive_vec4_adds(vec4 v, float s, vec4 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
	dest[3] = v[3] + s;
}

void olive_vec4_sub(vec4 a, vec4 b, vec4 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
	dest[3] = a[3] - b[3];
}

void olive_vec4_subs(vec4 v, float s, vec4 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
	dest[3] = v[3] - s;
}

void olive_vec4_mul(vec4 a, vec4 b, vec4 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
	dest[3] = a[3] * b[3];
}

void olive_vec4_scale(vec4 v, float s, vec4 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
	dest[2] = v[2] * s;
	dest[3] = v[3] * s;
}

void olive_vec4_scale_as(vec4 v, float s, vec4 dest) {
	float norm;
	norm = olive_vec4_norm(v);

	if (norm == 0.0f) {
		olive_vec4_zero(dest);
		return;
	}

	olive_vec4_scale(v, s / norm, dest);
}

void olive_vec4_div(vec4 a, vec4 b, vec4 dest) {
	dest[0] = a[0] / b[0];
	dest[1] = a[1] / b[1];
	dest[2] = a[2] / b[2];
	dest[3] = a[3] / b[3];
}

void olive_vec4_divs(vec4 v, float s, vec4 dest) {
	olive_vec4_scale(v, 1.0f / s, dest);
}

void olive_vec4_addadd(vec4 a, vec4 b, vec4 dest) {
	dest[0] += a[0] + b[0];
	dest[1] += a[1] + b[1];
	dest[2] += a[2] + b[2];
	dest[3] += a[3] + b[3];
}

void olive_vec4_subadd(vec4 a, vec4 b, vec4 dest) {
	dest[0] += a[0] - b[0];
	dest[1] += a[1] - b[1];
	dest[2] += a[2] - b[2];
	dest[3] += a[3] - b[3];
}

void olive_vec4_muladd(vec4 a, vec4 b, vec4 dest) {
	dest[0] += a[0] * b[0];
	dest[1] += a[1] * b[1];
	dest[2] += a[2] * b[2];
	dest[3] += a[3] * b[3];
}

void olive_vec4_muladds(vec4 a, float s, vec4 dest) {
	dest[0] += a[0] * s;
	dest[1] += a[1] * s;
	dest[2] += a[2] * s;
	dest[3] += a[3] * s;
}

void olive_vec4_maxadd(vec4 a, vec4 b, vec4 dest) {
	dest[0] += olive_max(a[0], b[0]);
	dest[1] += olive_max(a[1], b[1]);
	dest[2] += olive_max(a[2], b[2]);
	dest[3] += olive_max(a[3], b[3]);
}

void olive_vec4_minadd(vec4 a, vec4 b, vec4 dest) {
	dest[0] += olive_min(a[0], b[0]);
	dest[1] += olive_min(a[1], b[1]);
	dest[2] += olive_min(a[2], b[2]);
	dest[3] += olive_min(a[3], b[3]);
}

void olive_vec4_negate_to(vec4 v, vec4 dest) {
	dest[0] = -v[0];
	dest[1] = -v[1];
	dest[2] = -v[2];
	dest[3] = -v[3];
}

void olive_vec4_negate(vec4 v) { olive_vec4_negate_to(v, v); }

void olive_vec4_normalize_to(vec4 v, vec4 dest) {
	float norm;

	norm = olive_vec4_norm(v);

	if (norm == 0.0f) {
		olive_vec4_zero(dest);
		return;
	}

	olive_vec4_scale(v, 1.0f / norm, dest);
}

void olive_vec4_normalize(vec4 v) { olive_vec4_normalize_to(v, v); }

float olive_vec4_distance(vec4 a, vec4 b) {
	return sqrtf(olive_pow2(a[0] - b[0]) + olive_pow2(a[1] - b[1]) +
			olive_pow2(a[2] - b[2]) + olive_pow2(a[3] - b[3]));
}

float olive_vec4_distance2(vec4 a, vec4 b) {
	return olive_pow2(a[0] - b[0]) + olive_pow2(a[1] - b[1]) +
			olive_pow2(a[2] - b[2]) + olive_pow2(a[3] - b[3]);
}

void olive_vec4_maxv(vec4 a, vec4 b, vec4 dest) {
	dest[0] = olive_max(a[0], b[0]);
	dest[1] = olive_max(a[1], b[1]);
	dest[2] = olive_max(a[2], b[2]);
	dest[3] = olive_max(a[3], b[3]);
}

void olive_vec4_minv(vec4 a, vec4 b, vec4 dest) {
	dest[0] = olive_min(a[0], b[0]);
	dest[1] = olive_min(a[1], b[1]);
	dest[2] = olive_min(a[2], b[2]);
	dest[3] = olive_min(a[3], b[3]);
}

void olive_vec4_clamp(vec4 v, float minVal, float maxVal) {
	v[0] = olive_clamp(v[0], minVal, maxVal);
	v[1] = olive_clamp(v[1], minVal, maxVal);
	v[2] = olive_clamp(v[2], minVal, maxVal);
	v[3] = olive_clamp(v[3], minVal, maxVal);
}

void olive_vec4_lerp(vec4 from, vec4 to, float t, vec4 dest) {
	vec4 s, v;

	olive_vec4_broadcast(t, s);
	olive_vec4_sub(to, from, v);
	olive_vec4_mul(s, v, v);
	olive_vec4_add(from, v, dest);
}

void olive_vec4_lerpc(vec4 from, vec4 to, float t, vec4 dest) {
	olive_vec4_lerp(from, to, olive_clamp_zo(t), dest);
}

void olive_vec4_mix(vec4 from, vec4 to, float t, vec4 dest) {
	olive_vec4_lerp(from, to, t, dest);
}

void olive_vec4_mixc(vec4 from, vec4 to, float t, vec4 dest) {
	olive_vec4_lerpc(from, to, t, dest);
}

void olive_vec4_step_uni(float edge, vec4 x, vec4 dest) {
	dest[0] = olive_step(edge, x[0]);
	dest[1] = olive_step(edge, x[1]);
	dest[2] = olive_step(edge, x[2]);
	dest[3] = olive_step(edge, x[3]);
}

void olive_vec4_step(vec4 edge, vec4 x, vec4 dest) {
	dest[0] = olive_step(edge[0], x[0]);
	dest[1] = olive_step(edge[1], x[1]);
	dest[2] = olive_step(edge[2], x[2]);
	dest[3] = olive_step(edge[3], x[3]);
}

void olive_vec4_smoothstep_uni(float edge0, float edge1, vec4 x, vec4 dest) {
	dest[0] = olive_smoothstep(edge0, edge1, x[0]);
	dest[1] = olive_smoothstep(edge0, edge1, x[1]);
	dest[2] = olive_smoothstep(edge0, edge1, x[2]);
	dest[3] = olive_smoothstep(edge0, edge1, x[3]);
}

void olive_vec4_smoothstep(vec4 edge0, vec4 edge1, vec4 x, vec4 dest) {
	dest[0] = olive_smoothstep(edge0[0], edge1[0], x[0]);
	dest[1] = olive_smoothstep(edge0[1], edge1[1], x[1]);
	dest[2] = olive_smoothstep(edge0[2], edge1[2], x[2]);
	dest[3] = olive_smoothstep(edge0[3], edge1[3], x[3]);
}

void olive_vec4_smoothinterp(vec4 from, vec4 to, float t, vec4 dest) {
	vec4 s, v;

	/* from + smoothstep * (to - from) */
	olive_vec4_broadcast(olive_smooth(t), s);
	olive_vec4_sub(to, from, v);
	olive_vec4_mul(s, v, v);
	olive_vec4_add(from, v, dest);
}

void olive_vec4_smoothinterpc(vec4 from, vec4 to, float t, vec4 dest) {
	olive_vec4_smoothinterp(from, to, olive_clamp_zo(t), dest);
}

void olive_vec4_cubic(float s, vec4 dest) {
	float ss;

	ss = s * s;

	dest[0] = ss * s;
	dest[1] = ss;
	dest[2] = s;
	dest[3] = 1.0f;
}

void olive_vec4_swizzle(vec4 v, int mask, vec4 dest) {
	vec4 t;

	t[0] = v[(mask & (3 << 0))];
	t[1] = v[(mask & (3 << 2)) >> 2];
	t[2] = v[(mask & (3 << 4)) >> 4];
	t[3] = v[(mask & (3 << 6)) >> 6];

	olive_vec4_copy(t, dest);
}
