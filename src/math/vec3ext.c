#include "olive/math/utils.h"
#include "olive/types.h"
#include <math.h>
#include <stdbool.h>

void olive_vec3_broadcast(float val, vec3 d) { d[0] = d[1] = d[2] = val; }

void olive_vec3_fill(vec3 v, float val) { v[0] = v[1] = v[2] = val; }

bool olive_vec3_eq(vec3 v, float val) {
  return v[0] == val && v[0] == v[1] && v[0] == v[2];
}

bool olive_vec3_eq_eps(vec3 v, float val) {
  return fabsf(v[0] - val) <= FLT_EPSILON && fabsf(v[1] - val) <= FLT_EPSILON &&
         fabsf(v[2] - val) <= FLT_EPSILON;
}

bool olive_vec3_eq_all(vec3 v) { return olive_vec3_eq_eps(v, v[0]); }

bool olive_vec3_eqv(vec3 a, vec3 b) {
  return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}

bool olive_vec3_eqv_eps(vec3 a, vec3 b) {
  return fabsf(a[0] - b[0]) <= FLT_EPSILON &&
         fabsf(a[1] - b[1]) <= FLT_EPSILON && fabsf(a[2] - b[2]) <= FLT_EPSILON;
}

float olive_vec3_max(vec3 v) {
  float max;

  max = v[0];
  if (v[1] > max)
    max = v[1];
  if (v[2] > max)
    max = v[2];

  return max;
}

float olive_vec3_min(vec3 v) {
  float min;

  min = v[0];
  if (v[1] < min)
    min = v[1];
  if (v[2] < min)
    min = v[2];

  return min;
}

bool olive_vec3_isnan(vec3 v) {
  return isnan(v[0]) || isnan(v[1]) || isnan(v[2]);
}

bool olive_vec3_isinf(vec3 v) {
  return isinf(v[0]) || isinf(v[1]) || isinf(v[2]);
}

bool olive_vec3_isvalid(vec3 v) {
  return !olive_vec3_isnan(v) && !olive_vec3_isinf(v);
}

void olive_vec3_sign(vec3 v, vec3 dest) {
  dest[0] = olive_signf(v[0]);
  dest[1] = olive_signf(v[1]);
  dest[2] = olive_signf(v[2]);
}

void olive_vec3_abs(vec3 v, vec3 dest) {
  dest[0] = fabsf(v[0]);
  dest[1] = fabsf(v[1]);
  dest[2] = fabsf(v[2]);
}

void olive_vec3_fract(vec3 v, vec3 dest) {
  dest[0] = fminf(v[0] - floorf(v[0]), 0.999999940395355224609375f);
  dest[1] = fminf(v[1] - floorf(v[1]), 0.999999940395355224609375f);
  dest[2] = fminf(v[2] - floorf(v[2]), 0.999999940395355224609375f);
}

float olive_vec3_hadd(vec3 v) { return v[0] + v[1] + v[2]; }

void olive_vec3_sqrt(vec3 v, vec3 dest) {
  dest[0] = sqrtf(v[0]);
  dest[1] = sqrtf(v[1]);
  dest[2] = sqrtf(v[2]);
}
