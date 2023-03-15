#ifndef OLIVE_VEC4_H
#define OLIVE_VEC4_H

#include "olive/types.h"

#define OLIVE_VEC4_ONE_INIT                                                    \
  { 1.0f, 1.0f, 1.0f, 1.0f }
#define OLIVE_VEC4_BLACK_INIT                                                  \
  { 0.0f, 0.0f, 0.0f, 1.0f }
#define OLIVE_VEC4_ZERO_INIT                                                   \
  { 0.0f, 0.0f, 0.0f, 0.0f }

#define OLIVE_VEC4_ONE ((vec4)OLIVE_VEC4_ONE_INIT)
#define OLIVE_VEC4_BLACK ((vec4)OLIVE_VEC4_BLACK_INIT)
#define OLIVE_VEC4_ZERO ((vec4)OLIVE_VEC4_ZERO_INIT)

#define SHUFFLE4(z, y, x, w) (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))
#define OLIVE_XXXX SHUFFLE4(0, 0, 0, 0)
#define OLIVE_YYYY SHUFFLE4(1, 1, 1, 1)
#define OLIVE_ZZZZ SHUFFLE4(2, 2, 2, 2)
#define OLIVE_WWWW SHUFFLE4(3, 3, 3, 3)
#define OLIVE_WZYX SHUFFLE4(0, 1, 2, 3)

void olive_vec4(vec3 v3, float last, vec4 dest);
void olive_vec4_copy3(vec4 a, vec3 dest);
void olive_vec4_copy(vec4 v, vec4 dest);
void olive_vec4_ucopy(vec4 v, vec4 dest);
void olive_vec4_zero(vec4 v);
void olive_vec4_one(vec4 v);
float olive_vec4_dot(vec4 a, vec4 b);
float olive_vec4_norm2(vec4 v);
float olive_vec4_norm(vec4 v);
float olive_vec4_norm_one(vec4 v);
float olive_vec4_norm_inf(vec4 v);
void olive_vec4_add(vec4 a, vec4 b, vec4 dest);
void olive_vec4_adds(vec4 v, float s, vec4 dest);
void olive_vec4_sub(vec4 a, vec4 b, vec4 dest);
void olive_vec4_subs(vec4 v, float s, vec4 dest);
void olive_vec4_mul(vec4 a, vec4 b, vec4 dest);
void olive_vec4_scale(vec4 v, float s, vec4 dest);
void olive_vec4_scale_as(vec4 v, float s, vec4 dest);
void olive_vec4_div(vec4 a, vec4 b, vec4 dest);
void olive_vec4_divs(vec4 v, float s, vec4 dest);
void olive_vec4_addadd(vec4 a, vec4 b, vec4 dest);
void olive_vec4_subadd(vec4 a, vec4 b, vec4 dest);
void olive_vec4_muladd(vec4 a, vec4 b, vec4 dest);
void olive_vec4_muladds(vec4 a, float s, vec4 dest);
void olive_vec4_maxadd(vec4 a, vec4 b, vec4 dest);
void olive_vec4_minadd(vec4 a, vec4 b, vec4 dest);
void olive_vec4_negate_to(vec4 v, vec4 dest);
void olive_vec4_negate(vec4 v);
void olive_vec4_normalize_to(vec4 v, vec4 dest);
void olive_vec4_normalize(vec4 v);
float olive_vec4_distance(vec4 a, vec4 b);
float olive_vec4_distance2(vec4 a, vec4 b);
void olive_vec4_maxv(vec4 a, vec4 b, vec4 dest);
void olive_vec4_minv(vec4 a, vec4 b, vec4 dest);
void olive_vec4_clamp(vec4 v, float minVal, float maxVal);
void olive_vec4_lerp(vec4 from, vec4 to, float t, vec4 dest);
void olive_vec4_lerpc(vec4 from, vec4 to, float t, vec4 dest);
void olive_vec4_mix(vec4 from, vec4 to, float t, vec4 dest);
void olive_vec4_mixc(vec4 from, vec4 to, float t, vec4 dest);
void olive_vec4_step_uni(float edge, vec4 x, vec4 dest);
void olive_vec4_step(vec4 edge, vec4 x, vec4 dest);
void olive_vec4_smoothstep_uni(float edge0, float edge1, vec4 x, vec4 dest);
void olive_vec4_smoothstep(vec4 edge0, vec4 edge1, vec4 x, vec4 dest);
void olive_vec4_smoothinterp(vec4 from, vec4 to, float t, vec4 dest);
void olive_vec4_smoothinterpc(vec4 from, vec4 to, float t, vec4 dest);
void olive_vec4_cubic(float s, vec4 dest);
void olive_vec4_swizzle(vec4 v, int mask, vec4 dest);

#endif // OLIVE_VEC4_H
