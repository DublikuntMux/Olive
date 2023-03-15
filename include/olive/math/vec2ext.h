#ifndef OLIVE_VEC2_EXT_H
#define OLIVE_VEC2_EXT_H

#include "olive/types.h"
#include <stdbool.h>

void olive_vec2_fill(vec2 v, float val);
bool olive_vec2_eq(vec2 v, float val);
bool olive_vec2_eq_eps(vec2 v, float val);
bool olive_vec2_eq_all(vec2 v);
bool olive_vec2_eqv(vec2 a, vec2 b);
bool olive_vec2_eqv_eps(vec2 a, vec2 b);
float olive_vec2_max(vec2 v);
float olive_vec2_min(vec2 v);
bool olive_vec2_isnan(vec2 v);
bool olive_vec2_isinf(vec2 v);
bool olive_vec2_isvalid(vec2 v);
void olive_vec2_sign(vec2 v, vec2 dest);
void olive_vec2_abs(vec2 v, vec2 dest);
void olive_vec2_sqrt(vec2 v, vec2 dest);
void olive_vec2_complex_mul(vec2 a, vec2 b, vec2 dest);
void olive_vec2_complex_div(vec2 a, vec2 b, vec2 dest);
void olive_vec2_complex_conjugate(vec2 a, vec2 dest);

#endif // OLIVE_VEC2_EXT_H
