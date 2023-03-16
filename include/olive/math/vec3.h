#ifndef OLIVE_VEC3_H
#define OLIVE_VEC3_H

#include "olive/types.h"

#define OLIVE_VEC3_ONE_INIT \
	{ 1.0f, 1.0f, 1.0f }
#define OLIVE_VEC3_ZERO_INIT \
	{ 0.0f, 0.0f, 0.0f }

#define OLIVE_VEC3_ONE ((vec3)OLIVE_VEC3_ONE_INIT)
#define OLIVE_VEC3_ZERO ((vec3)OLIVE_VEC3_ZERO_INIT)

#define OLIVE_YUP ((vec3){ 0.0f, 1.0f, 0.0f })
#define OLIVE_ZUP ((vec3){ 0.0f, 0.0f, 1.0f })
#define OLIVE_XUP ((vec3){ 1.0f, 0.0f, 0.0f })
#define OLIVE_FORWARD ((vec3){ 0.0f, 0.0f, -1.0f })

#define SHUFFLE3(z, y, x) (((z) << 4) | ((y) << 2) | (x))
#define OLIVE_XXX SHUFFLE3(0, 0, 0)
#define OLIVE_YYY SHUFFLE3(1, 1, 1)
#define OLIVE_ZZZ SHUFFLE3(2, 2, 2)
#define OLIVE_ZYX SHUFFLE3(0, 1, 2)

void olive_vec3(vec4 v4, vec3 dest);
void olive_vec3_copy(vec3 a, vec3 dest);
void olive_vec3_zero(vec3 v);
void olive_vec3_one(vec3 v);
float olive_vec3_dot(vec3 a, vec3 b);
float olive_vec3_norm2(vec3 v);
float olive_vec3_norm(vec3 v);
float olive_vec3_norm_one(vec3 v);
float olive_vec3_norm_inf(vec3 v);
void olive_vec3_add(vec3 a, vec3 b, vec3 dest);
void olive_vec3_adds(vec3 v, float s, vec3 dest);
void olive_vec3_sub(vec3 a, vec3 b, vec3 dest);
void olive_vec3_subs(vec3 v, float s, vec3 dest);
void olive_vec3_mul(vec3 a, vec3 b, vec3 dest);
void olive_vec3_scale(vec3 v, float s, vec3 dest);
void olive_vec3_scale_as(vec3 v, float s, vec3 dest);
void olive_vec3_div(vec3 a, vec3 b, vec3 dest);
void olive_vec3_divs(vec3 v, float s, vec3 dest);
void olive_vec3_addadd(vec3 a, vec3 b, vec3 dest);
void olive_vec3_subadd(vec3 a, vec3 b, vec3 dest);
void olive_vec3_muladd(vec3 a, vec3 b, vec3 dest);
void olive_vec3_muladds(vec3 a, float s, vec3 dest);
void olive_vec3_maxadd(vec3 a, vec3 b, vec3 dest);
void olive_vec3_minadd(vec3 a, vec3 b, vec3 dest);
void olive_vec3_negate_to(vec3 v, vec3 dest);
void olive_vec3_negate(vec3 v);
void olive_vec3_normalize(vec3 v);
void olive_vec3_normalize_to(vec3 v, vec3 dest);
void olive_vec3_cross(vec3 a, vec3 b, vec3 dest);
void olive_vec3_crossn(vec3 a, vec3 b, vec3 dest);
float olive_vec3_angle(vec3 a, vec3 b);
void olive_vec3_rotate(vec3 v, float angle, vec3 axis);
void olive_vec3_rotate_m4(mat4 m, vec3 v, vec3 dest);
void olive_vec3_rotate_m3(mat3 m, vec3 v, vec3 dest);
void olive_vec3_proj(vec3 a, vec3 b, vec3 dest);
void olive_vec3_center(vec3 a, vec3 b, vec3 dest);
float olive_vec3_distance2(vec3 a, vec3 b);
float olive_vec3_distance(vec3 a, vec3 b);
void olive_vec3_maxv(vec3 a, vec3 b, vec3 dest);
void olive_vec3_minv(vec3 a, vec3 b, vec3 dest);
void olive_vec3_ortho(vec3 v, vec3 dest);
void olive_vec3_clamp(vec3 v, float minVal, float maxVal);
void olive_vec3_lerp(vec3 from, vec3 to, float t, vec3 dest);
void olive_vec3_lerpc(vec3 from, vec3 to, float t, vec3 dest);
void olive_vec3_mix(vec3 from, vec3 to, float t, vec3 dest);
void olive_vec3_mixc(vec3 from, vec3 to, float t, vec3 dest);
void olive_vec3_step_uni(float edge, vec3 x, vec3 dest);
void olive_vec3_step(vec3 edge, vec3 x, vec3 dest);
void olive_vec3_smoothstep_uni(float edge0, float edge1, vec3 x, vec3 dest);
void olive_vec3_smoothstep(vec3 edge0, vec3 edge1, vec3 x, vec3 dest);
void olive_vec3_smoothinterp(vec3 from, vec3 to, float t, vec3 dest);
void olive_vec3_smoothinterpc(vec3 from, vec3 to, float t, vec3 dest);
void olive_vec3_swizzle(vec3 v, int mask, vec3 dest);
void olive_cross(vec3 a, vec3 b, vec3 d);
float olive_dot(vec3 a, vec3 b);
void olive_normalize(vec3 v);
void olive_normalize_to(vec3 v, vec3 dest);

#endif // OLIVE_VEC3_H
