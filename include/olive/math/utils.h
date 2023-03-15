#ifndef OLIVE_MUTILS_H
#define OLIVE_MUTILS_H

#include "olive/types.h"
#include <stdbool.h>

int olive_sign(int val);
float olive_signf(float val);
float olive_rad(float deg);
float olive_deg(float rad);
void olive_make_rad(float *deg);
void olive_make_deg(float *rad);
float olive_pow2(float x);
float olive_min(float a, float b);
float olive_max(float a, float b);
float olive_clamp(float val, float minVal, float maxVal);
float olive_clamp_zo(float val);
float olive_lerp(float from, float to, float t);
float olive_lerpc(float from, float to, float t);
float olive_step(float edge, float x);
float olive_smooth(float t);
float olive_smoothstep(float edge0, float edge1, float x);
float olive_smoothinterp(float from, float to, float t);
float olive_smoothinterpc(float from, float to, float t);
bool olive_eq(float a, float b);
float olive_percent(float from, float to, float current);
float olive_percentc(float from, float to, float current);
void olive_swap(int *__restrict a, int *__restrict b);
void olive_swapf(float *__restrict a, float *__restrict b);
bool olivec_barycentric(int x1, int y1, int x2, int y2, int x3, int y3, int xp,
                        int yp, int *u1, int *u2, int *det);

#endif // OLIVE_MUTILS_H
