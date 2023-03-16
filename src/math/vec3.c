#include "olive/math/vec3ext.h"
#include "olive/math/vec4.h"
#include "olive/types.h"
#include "olive/utils/math.h"
#include <math.h>

void olive_vec3(vec4 v4, vec3 dest) {
	dest[0] = v4[0];
	dest[1] = v4[1];
	dest[2] = v4[2];
}

void olive_vec3_copy(vec3 a, vec3 dest) {
	dest[0] = a[0];
	dest[1] = a[1];
	dest[2] = a[2];
}

void olive_vec3_zero(vec3 v) { v[0] = v[1] = v[2] = 0.0f; }

void olive_vec3_one(vec3 v) { v[0] = v[1] = v[2] = 1.0f; }

float olive_vec3_dot(vec3 a, vec3 b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float olive_vec3_norm2(vec3 v) { return olive_vec3_dot(v, v); }

float olive_vec3_norm(vec3 v) { return sqrtf(olive_vec3_norm2(v)); }

float olive_vec3_norm_one(vec3 v) {
	vec3 t;
	olive_vec3_abs(v, t);
	return olive_vec3_hadd(t);
}

float olive_vec3_norm_inf(vec3 v) {
	vec3 t;
	olive_vec3_abs(v, t);
	return olive_vec3_max(t);
}

void olive_vec3_add(vec3 a, vec3 b, vec3 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
}

void olive_vec3_adds(vec3 v, float s, vec3 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
}

void olive_vec3_sub(vec3 a, vec3 b, vec3 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
}

void olive_vec3_subs(vec3 v, float s, vec3 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
}

void olive_vec3_mul(vec3 a, vec3 b, vec3 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
}

void olive_vec3_scale(vec3 v, float s, vec3 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
	dest[2] = v[2] * s;
}

void olive_vec3_scale_as(vec3 v, float s, vec3 dest) {
	float norm;
	norm = olive_vec3_norm(v);

	if (norm == 0.0f) {
		olive_vec3_zero(dest);
		return;
	}

	olive_vec3_scale(v, s / norm, dest);
}

void olive_vec3_div(vec3 a, vec3 b, vec3 dest) {
	dest[0] = a[0] / b[0];
	dest[1] = a[1] / b[1];
	dest[2] = a[2] / b[2];
}

void olive_vec3_divs(vec3 v, float s, vec3 dest) {
	dest[0] = v[0] / s;
	dest[1] = v[1] / s;
	dest[2] = v[2] / s;
}

void olive_vec3_addadd(vec3 a, vec3 b, vec3 dest) {
	dest[0] += a[0] + b[0];
	dest[1] += a[1] + b[1];
	dest[2] += a[2] + b[2];
}

void olive_vec3_subadd(vec3 a, vec3 b, vec3 dest) {
	dest[0] += a[0] - b[0];
	dest[1] += a[1] - b[1];
	dest[2] += a[2] - b[2];
}

void olive_vec3_muladd(vec3 a, vec3 b, vec3 dest) {
	dest[0] += a[0] * b[0];
	dest[1] += a[1] * b[1];
	dest[2] += a[2] * b[2];
}

void olive_vec3_muladds(vec3 a, float s, vec3 dest) {
	dest[0] += a[0] * s;
	dest[1] += a[1] * s;
	dest[2] += a[2] * s;
}

void olive_vec3_maxadd(vec3 a, vec3 b, vec3 dest) {
	dest[0] += olive_max(a[0], b[0]);
	dest[1] += olive_max(a[1], b[1]);
	dest[2] += olive_max(a[2], b[2]);
}

void olive_vec3_minadd(vec3 a, vec3 b, vec3 dest) {
	dest[0] += olive_min(a[0], b[0]);
	dest[1] += olive_min(a[1], b[1]);
	dest[2] += olive_min(a[2], b[2]);
}

void olive_vec3_negate_to(vec3 v, vec3 dest) {
	dest[0] = -v[0];
	dest[1] = -v[1];
	dest[2] = -v[2];
}

void olive_vec3_negate(vec3 v) { olive_vec3_negate_to(v, v); }

void olive_vec3_normalize(vec3 v) {
	float norm;

	norm = olive_vec3_norm(v);

	if (norm == 0.0f) {
		v[0] = v[1] = v[2] = 0.0f;
		return;
	}

	olive_vec3_scale(v, 1.0f / norm, v);
}

void olive_vec3_normalize_to(vec3 v, vec3 dest) {
	float norm;

	norm = olive_vec3_norm(v);

	if (norm == 0.0f) {
		olive_vec3_zero(dest);
		return;
	}

	olive_vec3_scale(v, 1.0f / norm, dest);
}

void olive_vec3_cross(vec3 a, vec3 b, vec3 dest) {
	vec3 c;
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	olive_vec3_copy(c, dest);
}

void olive_vec3_crossn(vec3 a, vec3 b, vec3 dest) {
	olive_vec3_cross(a, b, dest);
	olive_vec3_normalize(dest);
}

float olive_vec3_angle(vec3 a, vec3 b) {
	float norm, dot;
	norm = 1.0f / (olive_vec3_norm(a) * olive_vec3_norm(b));
	dot = olive_vec3_dot(a, b) * norm;

	if (dot > 1.0f)
		return 0.0f;
	else if (dot < -1.0f)
		return PI;

	return acosf(dot);
}

void olive_vec3_rotate(vec3 v, float angle, vec3 axis) {
	vec3 v1, v2, k;
	float c, s;

	c = cosf(angle);
	s = sinf(angle);

	olive_vec3_normalize_to(axis, k);

	olive_vec3_scale(v, c, v1);

	olive_vec3_cross(k, v, v2);
	olive_vec3_scale(v2, s, v2);

	olive_vec3_add(v1, v2, v1);

	olive_vec3_scale(k, olive_vec3_dot(k, v) * (1.0f - c), v2);
	olive_vec3_add(v1, v2, v);
}

void olive_vec3_rotate_m4(mat4 m, vec3 v, vec3 dest) {
	vec4 x, y, z, res;

	olive_vec4_normalize_to(m[0], x);
	olive_vec4_normalize_to(m[1], y);
	olive_vec4_normalize_to(m[2], z);

	olive_vec4_scale(x, v[0], res);
	olive_vec4_muladds(y, v[1], res);
	olive_vec4_muladds(z, v[2], res);

	olive_vec3(res, dest);
}

void olive_vec3_rotate_m3(mat3 m, vec3 v, vec3 dest) {
	vec4 res, x, y, z;

	olive_vec4(m[0], 0.0f, x);
	olive_vec4(m[1], 0.0f, y);
	olive_vec4(m[2], 0.0f, z);

	olive_vec4_normalize(x);
	olive_vec4_normalize(y);
	olive_vec4_normalize(z);

	olive_vec4_scale(x, v[0], res);
	olive_vec4_muladds(y, v[1], res);
	olive_vec4_muladds(z, v[2], res);

	olive_vec3(res, dest);
}

void olive_vec3_proj(vec3 a, vec3 b, vec3 dest) {
	olive_vec3_scale(b, olive_vec3_dot(a, b) / olive_vec3_norm2(b), dest);
}

void olive_vec3_center(vec3 a, vec3 b, vec3 dest) {
	olive_vec3_add(a, b, dest);
	olive_vec3_scale(dest, 0.5f, dest);
}

float olive_vec3_distance2(vec3 a, vec3 b) {
	return olive_pow2(a[0] - b[0]) + olive_pow2(a[1] - b[1]) +
			olive_pow2(a[2] - b[2]);
}

float olive_vec3_distance(vec3 a, vec3 b) {
	return sqrtf(olive_vec3_distance2(a, b));
}

void olive_vec3_maxv(vec3 a, vec3 b, vec3 dest) {
	dest[0] = olive_max(a[0], b[0]);
	dest[1] = olive_max(a[1], b[1]);
	dest[2] = olive_max(a[2], b[2]);
}

void olive_vec3_minv(vec3 a, vec3 b, vec3 dest) {
	dest[0] = olive_min(a[0], b[0]);
	dest[1] = olive_min(a[1], b[1]);
	dest[2] = olive_min(a[2], b[2]);
}

void olive_vec3_ortho(vec3 v, vec3 dest) {
	float ignore;
	float f = modff(fabsf(v[0]) + 0.5f, &ignore);
	vec3 result = { -v[1], v[0] - f * v[2], f * v[1] };
	olive_vec3_copy(result, dest);
}

void olive_vec3_clamp(vec3 v, float minVal, float maxVal) {
	v[0] = olive_clamp(v[0], minVal, maxVal);
	v[1] = olive_clamp(v[1], minVal, maxVal);
	v[2] = olive_clamp(v[2], minVal, maxVal);
}

void olive_vec3_lerp(vec3 from, vec3 to, float t, vec3 dest) {
	vec3 s, v;

	/* from + s * (to - from) */
	olive_vec3_broadcast(t, s);
	olive_vec3_sub(to, from, v);
	olive_vec3_mul(s, v, v);
	olive_vec3_add(from, v, dest);
}

void olive_vec3_lerpc(vec3 from, vec3 to, float t, vec3 dest) {
	olive_vec3_lerp(from, to, olive_clamp_zo(t), dest);
}

void olive_vec3_mix(vec3 from, vec3 to, float t, vec3 dest) {
	olive_vec3_lerp(from, to, t, dest);
}

void olive_vec3_mixc(vec3 from, vec3 to, float t, vec3 dest) {
	olive_vec3_lerpc(from, to, t, dest);
}

void olive_vec3_step_uni(float edge, vec3 x, vec3 dest) {
	dest[0] = olive_step(edge, x[0]);
	dest[1] = olive_step(edge, x[1]);
	dest[2] = olive_step(edge, x[2]);
}

void olive_vec3_step(vec3 edge, vec3 x, vec3 dest) {
	dest[0] = olive_step(edge[0], x[0]);
	dest[1] = olive_step(edge[1], x[1]);
	dest[2] = olive_step(edge[2], x[2]);
}

void olive_vec3_smoothstep_uni(float edge0, float edge1, vec3 x, vec3 dest) {
	dest[0] = olive_smoothstep(edge0, edge1, x[0]);
	dest[1] = olive_smoothstep(edge0, edge1, x[1]);
	dest[2] = olive_smoothstep(edge0, edge1, x[2]);
}

void olive_vec3_smoothstep(vec3 edge0, vec3 edge1, vec3 x, vec3 dest) {
	dest[0] = olive_smoothstep(edge0[0], edge1[0], x[0]);
	dest[1] = olive_smoothstep(edge0[1], edge1[1], x[1]);
	dest[2] = olive_smoothstep(edge0[2], edge1[2], x[2]);
}

void olive_vec3_smoothinterp(vec3 from, vec3 to, float t, vec3 dest) {
	vec3 s, v;

	olive_vec3_broadcast(olive_smooth(t), s);
	olive_vec3_sub(to, from, v);
	olive_vec3_mul(s, v, v);
	olive_vec3_add(from, v, dest);
}

void olive_vec3_smoothinterpc(vec3 from, vec3 to, float t, vec3 dest) {
	olive_vec3_smoothinterp(from, to, olive_clamp_zo(t), dest);
}

void olive_vec3_swizzle(vec3 v, int mask, vec3 dest) {
	vec3 t;

	t[0] = v[(mask & (3 << 0))];
	t[1] = v[(mask & (3 << 2)) >> 2];
	t[2] = v[(mask & (3 << 4)) >> 4];

	olive_vec3_copy(t, dest);
}

void olive_cross(vec3 a, vec3 b, vec3 d) { olive_vec3_cross(a, b, d); }

float olive_dot(vec3 a, vec3 b) { return olive_vec3_dot(a, b); }

void olive_normalize(vec3 v) { olive_vec3_normalize(v); }

void olive_normalize_to(vec3 v, vec3 dest) { olive_vec3_normalize_to(v, dest); }
