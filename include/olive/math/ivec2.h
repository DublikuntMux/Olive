#ifndef OLIVE_IVEC2_H
#define OLIVE_IVEC2_H

#include "olive/types.h"

#define IVEC2_ONE_INIT \
	{ 1, 1 }
#define IVEC2_ZERO_INIT \
	{ 0, 0 }

#define IVEC2_ONE ((ivec2)IVEC2_ONE_INIT)
#define IVEC2_ZERO ((ivec2)IVEC2_ZERO_INIT)

void olive_ivec2(int *__restrict v, ivec2 dest);
void olive_ivec2_copy(ivec2 a, ivec2 dest);
void olive_ivec2_zero(ivec2 v);
void olive_ivec2_one(ivec2 v);
void olive_ivec2_add(ivec2 a, ivec2 b, ivec2 dest);
void olive_ivec2_adds(ivec2 v, int s, ivec2 dest);
void olive_ivec2_sub(ivec2 a, ivec2 b, ivec2 dest);
void olive_ivec2_subs(ivec2 v, int s, ivec2 dest);
void olive_ivec2_mul(ivec2 a, ivec2 b, ivec2 dest);
void olive_ivec2_scale(ivec2 v, int s, ivec2 dest);
int olive_ivec2_distance2(ivec2 a, ivec2 b);
float olive_ivec2_distance(ivec2 a, ivec2 b);
void olive_ivec2_maxv(ivec2 a, ivec2 b, ivec2 dest);
void olive_ivec2_minv(ivec2 a, ivec2 b, ivec2 dest);
void olive_ivec2_clamp(ivec2 v, int minVal, int maxVal);
void olive_ivec2_abs(ivec2 v, ivec2 dest);

#endif // OLIVE_IVEC2_H
