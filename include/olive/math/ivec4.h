#ifndef OLIVE_IVEC4_H
#define OLIVE_IVEC4_H

#include "olive/types.h"

#define IVEC4_ONE_INIT                                                         \
  { 1, 1, 1, 1 }
#define IVEC4_ZERO_INIT                                                        \
  { 0, 0, 0, 0 }

#define IVEC4_ONE ((ivec4)IVEC4_ONE_INIT)
#define IVEC4_ZERO ((ivec4)IVEC4_ZERO_INIT)

void olive_ivec4(ivec3 v3, int last, ivec4 dest);
void olive_ivec4_copy(ivec4 a, ivec4 dest);
void olive_ivec4_zero(ivec4 v);
void olive_ivec4_one(ivec4 v);
void olive_ivec4_add(ivec4 a, ivec4 b, ivec4 dest);
void olive_ivec4_adds(ivec4 v, int s, ivec4 dest);
void olive_ivec4_sub(ivec4 a, ivec4 b, ivec4 dest);
void olive_ivec4_subs(ivec4 v, int s, ivec4 dest);
void olive_ivec4_mul(ivec4 a, ivec4 b, ivec4 dest);
void olive_ivec4_scale(ivec4 v, int s, ivec4 dest);
int olive_ivec4_distance2(ivec4 a, ivec4 b);
float olive_ivec4_distance(ivec4 a, ivec4 b);
void olive_ivec4_maxv(ivec4 a, ivec4 b, ivec4 dest);
void olive_ivec4_minv(ivec4 a, ivec4 b, ivec4 dest);
void olive_ivec4_clamp(ivec4 v, int minVal, int maxVal);
void olive_ivec4_abs(ivec4 v, ivec4 dest);

#endif // OLIVE_IVEC4_H
