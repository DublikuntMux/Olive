#ifndef OLIVE_VEC2_H
#define OLIVE_VEC2_H

#include "olive/types.h"

#define OLIVE_VEC2_ONE_INIT \
	{ 1.0f, 1.0f }
#define OLIVE_VEC2_ZERO_INIT \
	{ 0.0f, 0.0f }

#define OLIVE_VEC2_ONE ((vec2)OLIVE_VEC2_ONE_INIT)
#define OLIVE_VEC2_ZERO ((vec2)OLIVE_VEC2_ZERO_INIT)

void olive_vec2(vec3 v3, vec2 dest);
void olive_project_3d_2d(vec3 v3, vec2 dest);
void olive_vec2_copy(vec2 a, vec2 dest);
void olive_vec2_zero(vec2 v);
void olive_vec2_one(vec2 v);
float olive_vec2_dot(vec2 a, vec2 b);
float olive_vec2_cross(vec2 a, vec2 b);
float olive_vec2_norm2(vec2 v);
float olive_vec2_norm(vec2 vec);
void olive_vec2_add(vec2 a, vec2 b, vec2 dest);
void olive_vec2_adds(vec2 v, float s, vec2 dest);
void olive_vec2_sub(vec2 a, vec2 b, vec2 dest);
void olive_vec2_subs(vec2 v, float s, vec2 dest);
void olive_vec2_mul(vec2 a, vec2 b, vec2 dest);
void olive_vec2_scale(vec2 v, float s, vec2 dest);
void olive_vec2_scale_as(vec2 v, float s, vec2 dest);
void olive_vec2_div(vec2 a, vec2 b, vec2 dest);
void olive_vec2_divs(vec2 v, float s, vec2 dest);
void olive_vec2_addadd(vec2 a, vec2 b, vec2 dest);
void olive_vec2_subadd(vec2 a, vec2 b, vec2 dest);
void olive_vec2_muladd(vec2 a, vec2 b, vec2 dest);
void olive_vec2_muladds(vec2 a, float s, vec2 dest);
void olive_vec2_maxadd(vec2 a, vec2 b, vec2 dest);
void olive_vec2_minadd(vec2 a, vec2 b, vec2 dest);
void olive_vec2_negate_to(vec2 v, vec2 dest);
void olive_vec2_negate(vec2 v);
void olive_vec2_normalize(vec2 v);
void olive_vec2_normalize_to(vec2 v, vec2 dest);
void olive_vec2_rotate(vec2 v, float angle, vec2 dest);
float olive_vec2_distance2(vec2 a, vec2 b);
float olive_vec2_distance(vec2 a, vec2 b);
void olive_vec2_maxv(vec2 a, vec2 b, vec2 dest);
void olive_vec2_minv(vec2 a, vec2 b, vec2 dest);
void olive_vec2_clamp(vec2 v, float minval, float maxval);
void olive_vec2_lerp(vec2 from, vec2 to, float t, vec2 dest);

#endif // OLIVE_VEC2_H
