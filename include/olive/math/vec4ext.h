#ifndef OLIVE_VEC4_EXT_H
#define OLIVE_VEC4_EXT_H

#include "olive/types.h"
#include <stdbool.h>

void olive_vec4_broadcast(float val, vec4 d);
void olive_vec4_fill(vec4 v, float val);
bool olive_vec4_eq(vec4 v, float val);
bool olive_vec4_eq_eps(vec4 v, float val);
bool olive_vec4_eq_all(vec4 v);
bool olive_vec4_eqv(vec4 a, vec4 b);
bool olive_vec4_eqv_eps(vec4 a, vec4 b);
float olive_vec4_max(vec4 v);
float olive_vec4_min(vec4 v);
bool olive_vec4_isnan(vec4 v);
bool olive_vec4_isinf(vec4 v);
bool olive_vec4_isvalid(vec4 v);
void olive_vec4_sign(vec4 v, vec4 dest);
void olive_vec4_abs(vec4 v, vec4 dest);
void olive_vec4_fract(vec4 v, vec4 dest);
float olive_vec4_hadd(vec4 v);
void olive_vec4_sqrt(vec4 v, vec4 dest);

#endif // OLIVE_VEC4_EXT_H
