#include "olive/types.h"
#include <math.h>
#include <stdlib.h>

void olive_ivec2(int *__restrict v, ivec2 dest) {
  dest[0] = v[0];
  dest[1] = v[1];
}

void olive_ivec2_copy(ivec2 a, ivec2 dest) {
  dest[0] = a[0];
  dest[1] = a[1];
}

void olive_ivec2_zero(ivec2 v) { v[0] = v[1] = 0; }

void olive_ivec2_one(ivec2 v) { v[0] = v[1] = 1; }

void olive_ivec2_add(ivec2 a, ivec2 b, ivec2 dest) {
  dest[0] = a[0] + b[0];
  dest[1] = a[1] + b[1];
}

void olive_ivec2_adds(ivec2 v, int s, ivec2 dest) {
  dest[0] = v[0] + s;
  dest[1] = v[1] + s;
}

void olive_ivec2_sub(ivec2 a, ivec2 b, ivec2 dest) {
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
}

void olive_ivec2_subs(ivec2 v, int s, ivec2 dest) {
  dest[0] = v[0] - s;
  dest[1] = v[1] - s;
}

void olive_ivec2_mul(ivec2 a, ivec2 b, ivec2 dest) {
  dest[0] = a[0] * b[0];
  dest[1] = a[1] * b[1];
}

void olive_ivec2_scale(ivec2 v, int s, ivec2 dest) {
  dest[0] = v[0] * s;
  dest[1] = v[1] * s;
}

int olive_ivec2_distance2(ivec2 a, ivec2 b) {
  int xd, yd;
  xd = a[0] - b[0];
  yd = a[1] - b[1];
  return xd * xd + yd * yd;
}

float olive_ivec2_distance(ivec2 a, ivec2 b) {
  return sqrtf((float)olive_ivec2_distance2(a, b));
}

void olive_ivec2_maxv(ivec2 a, ivec2 b, ivec2 dest) {
  dest[0] = a[0] > b[0] ? a[0] : b[0];
  dest[1] = a[1] > b[1] ? a[1] : b[1];
}

void olive_ivec2_minv(ivec2 a, ivec2 b, ivec2 dest) {
  dest[0] = a[0] < b[0] ? a[0] : b[0];
  dest[1] = a[1] < b[1] ? a[1] : b[1];
}

void olive_ivec2_clamp(ivec2 v, int minVal, int maxVal) {
  if (v[0] < minVal)
    v[0] = minVal;
  else if (v[0] > maxVal)
    v[0] = maxVal;

  if (v[1] < minVal)
    v[1] = minVal;
  else if (v[1] > maxVal)
    v[1] = maxVal;
}

void olive_ivec2_abs(ivec2 v, ivec2 dest) {
  dest[0] = abs(v[0]);
  dest[1] = abs(v[1]);
}
