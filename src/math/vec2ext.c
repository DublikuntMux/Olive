#include "olive/math/utils.h"
#include "olive/types.h"
#include <math.h>
#include <stdbool.h>

void olive_vec2_fill(vec2 v, float val) { v[0] = v[1] = val; }

bool olive_vec2_eq(vec2 v, float val) { return v[0] == val && v[0] == v[1]; }

bool olive_vec2_eq_eps(vec2 v, float val) {
  return fabsf(v[0] - val) <= FLT_EPSILON && fabsf(v[1] - val) <= FLT_EPSILON;
}

bool olive_vec2_eq_all(vec2 v) { return olive_vec2_eq_eps(v, v[0]); }

bool olive_vec2_eqv(vec2 a, vec2 b) { return a[0] == b[0] && a[1] == b[1]; }

bool olive_vec2_eqv_eps(vec2 a, vec2 b) {
  return fabsf(a[0] - b[0]) <= FLT_EPSILON && fabsf(a[1] - b[1]) <= FLT_EPSILON;
}

float olive_vec2_max(vec2 v) { return olive_max(v[0], v[1]); }

float olive_vec2_min(vec2 v) { return olive_min(v[0], v[1]); }

bool olive_vec2_isnan(vec2 v) { return isnan(v[0]) || isnan(v[1]); }

bool olive_vec2_isinf(vec2 v) { return isinf(v[0]) || isinf(v[1]); }

bool olive_vec2_isvalid(vec2 v) {
  return !olive_vec2_isnan(v) && !olive_vec2_isinf(v);
}

void olive_vec2_sign(vec2 v, vec2 dest) {
  dest[0] = olive_signf(v[0]);
  dest[1] = olive_signf(v[1]);
}

void olive_vec2_abs(vec2 v, vec2 dest) {
  dest[0] = fabsf(v[0]);
  dest[1] = fabsf(v[1]);
}

void olive_vec2_sqrt(vec2 v, vec2 dest) {
  dest[0] = sqrtf(v[0]);
  dest[1] = sqrtf(v[1]);
}

void olive_vec2_complex_mul(vec2 a, vec2 b, vec2 dest) {
  float tr, ti;
  tr = a[0] * b[0] - a[1] * b[1];
  ti = a[0] * b[1] + a[1] * b[0];
  dest[0] = tr;
  dest[1] = ti;
}

void olive_vec2_complex_div(vec2 a, vec2 b, vec2 dest) {
  float tr, ti;
  float const ibnorm2 = 1.0f / (b[0] * b[0] + b[1] * b[1]);
  tr = ibnorm2 * (a[0] * b[0] + a[1] * b[1]);
  ti = ibnorm2 * (a[1] * b[0] - a[0] * b[1]);
  dest[0] = tr;
  dest[1] = ti;
}

void olive_vec2_complex_conjugate(vec2 a, vec2 dest) {
  dest[0] = a[0];
  dest[1] = -a[1];
}
