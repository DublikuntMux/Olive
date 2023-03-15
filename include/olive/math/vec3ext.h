#ifndef OLIVE_VEC3_EXT_H
#define OLIVE_VEC3_EXT_H

#include "olive/types.h"
#include <stdbool.h>

void olive_vec3_broadcast(float val, vec3 d);
void olive_vec3_fill(vec3 v, float val);
bool olive_vec3_eq(vec3 v, float val);
bool olive_vec3_eq_eps(vec3 v, float val);
bool olive_vec3_eq_all(vec3 v);
bool olive_vec3_eqv(vec3 a, vec3 b);
bool olive_vec3_eqv_eps(vec3 a, vec3 b);
float olive_vec3_max(vec3 v);
float olive_vec3_min(vec3 v);
bool olive_vec3_isnan(vec3 v);
bool olive_vec3_isinf(vec3 v);
bool olive_vec3_isvalid(vec3 v);
void olive_vec3_sign(vec3 v, vec3 dest);
void olive_vec3_abs(vec3 v, vec3 dest);
void olive_vec3_fract(vec3 v, vec3 dest);
float olive_vec3_hadd(vec3 v);
void olive_vec3_sqrt(vec3 v, vec3 dest);

#endif // OLIVE_VEC3_EXT_H
