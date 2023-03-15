#ifndef OLIVE_IVEC2_H
#define OLIVE_IVEC2_H

#include "olive/types.h"

#define IVEC3_ONE_INIT                                                         \
  { 1, 1, 1 }
#define IVEC3_ZERO_INIT                                                        \
  { 0, 0, 0 }

#define IVEC3_ONE ((ivec3)IVEC3_ONE_INIT)
#define IVEC3_ZERO ((ivec3)IVEC3_ZERO_INIT)

void olive_ivec3(ivec4 v4, ivec3 dest);
void olive_ivec3_copy(ivec3 a, ivec3 dest);
void olive_ivec3_zero(ivec3 v);
void olive_ivec3_one(ivec3 v);
void olive_ivec3_add(ivec3 a, ivec3 b, ivec3 dest);
void olive_ivec3_adds(ivec3 v, int s, ivec3 dest);
void olive_ivec3_sub(ivec3 a, ivec3 b, ivec3 dest);
void olive_ivec3_subs(ivec3 v, int s, ivec3 dest);
void olive_ivec3_mul(ivec3 a, ivec3 b, ivec3 dest);
void olive_ivec3_scale(ivec3 v, int s, ivec3 dest);
int olive_ivec3_distance2(ivec3 a, ivec3 b);
float olive_ivec3_distance(ivec3 a, ivec3 b);
void olive_ivec3_maxv(ivec3 a, ivec3 b, ivec3 dest);
void olive_ivec3_minv(ivec3 a, ivec3 b, ivec3 dest);
void olive_ivec3_clamp(ivec3 v, int minVal, int maxVal);
void olive_ivec3_abs(ivec3 v, ivec3 dest);

#endif // OLIVE_IVEC2_H
