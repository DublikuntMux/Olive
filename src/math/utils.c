#include "olive/types.h"
#include <math.h>
#include <stdbool.h>

int olive_sign(int val) { return ((val >> 31) - (-val >> 31)); }

float olive_signf(float val) { return (float)((val > 0.0f) - (val < 0.0f)); }

float olive_rad(float deg) { return deg * PIf / 180.0f; }

float olive_deg(float rad) { return rad * 180.0f / PIf; }

void olive_make_rad(float *deg) { *deg = *deg * PIf / 180.0f; }

void olive_make_deg(float *rad) { *rad = *rad * 180.0f / PIf; }

float olive_pow2(float x) { return x * x; }

float olive_min(float a, float b) {
  if (a < b)
    return a;
  return b;
}

float olive_max(float a, float b) {
  if (a > b)
    return a;
  return b;
}

float olive_clamp(float val, float minVal, float maxVal) {
  return olive_min(olive_max(val, minVal), maxVal);
}

float olive_clamp_zo(float val) { return olive_clamp(val, 0.0f, 1.0f); }

float olive_lerp(float from, float to, float t) {
  return from + t * (to - from);
}

float olive_lerpc(float from, float to, float t) {
  return olive_lerp(from, to, olive_clamp_zo(t));
}

float olive_step(float edge, float x) { return (x < edge) ? 0.0f : 1.0f; }

float olive_smooth(float t) { return t * t * (3.0f - 2.0f * t); }

float olive_smoothstep(float edge0, float edge1, float x) {
  float t;
  t = olive_clamp_zo((x - edge0) / (edge1 - edge0));
  return olive_smooth(t);
}

float olive_smoothinterp(float from, float to, float t) {
  return from + olive_smooth(t) * (to - from);
}

float olive_smoothinterpc(float from, float to, float t) {
  return olive_smoothinterp(from, to, olive_clamp_zo(t));
}

bool olive_eq(float a, float b) { return fabsf(a - b) <= FLT_EPSILON; }

float olive_percent(float from, float to, float current) {
  float t;

  if ((t = to - from) == 0.0f)
    return 1.0f;

  return (current - from) / t;
}

float olive_percentc(float from, float to, float current) {
  return olive_clamp_zo(olive_percent(from, to, current));
}

void olive_swap(int *__restrict a, int *__restrict b) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

void olive_swapf(float *__restrict a, float *__restrict b) {
  float t;
  t = *a;
  *a = *b;
  *b = t;
}

bool olivec_barycentric(int x1, int y1, int x2, int y2, int x3, int y3, int xp,
                        int yp, int *u1, int *u2, int *det) {
  *det = ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3));
  *u1 = ((y2 - y3) * (xp - x3) + (x3 - x2) * (yp - y3));
  *u2 = ((y3 - y1) * (xp - x3) + (x1 - x3) * (yp - y3));
  int u3 = *det - *u1 - *u2;
  return ((olive_sign(*u1) == olive_sign(*det) || *u1 == 0) &&
          (olive_sign(*u2) == olive_sign(*det) || *u2 == 0) &&
          (olive_sign(u3) == olive_sign(*det) || u3 == 0));
}
