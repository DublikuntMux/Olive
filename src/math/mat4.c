#include "olive/math/mat4.h"
#include "olive/math/vec3.h"
#include "olive/math/vec4.h"
#include "olive/types.h"
#include <math.h>

void olive_mat4_ucopy(mat4 mat, mat4 dest) {
  dest[0][0] = mat[0][0];
  dest[1][0] = mat[1][0];
  dest[0][1] = mat[0][1];
  dest[1][1] = mat[1][1];
  dest[0][2] = mat[0][2];
  dest[1][2] = mat[1][2];
  dest[0][3] = mat[0][3];
  dest[1][3] = mat[1][3];

  dest[2][0] = mat[2][0];
  dest[3][0] = mat[3][0];
  dest[2][1] = mat[2][1];
  dest[3][1] = mat[3][1];
  dest[2][2] = mat[2][2];
  dest[3][2] = mat[3][2];
  dest[2][3] = mat[2][3];
  dest[3][3] = mat[3][3];
}

void olive_mat4_copy(mat4 mat, mat4 dest) { olive_mat4_ucopy(mat, dest); }

void olive_mat4_identity(mat4 mat) {
  __attribute((aligned(16))) mat4 t = OLIVE_MAT4_IDENTITY_INIT;
  olive_mat4_copy(t, mat);
}

void olive_mat4_identity_array(mat4 *__restrict mat, size_t count) {
  __attribute((aligned(16))) mat4 t = OLIVE_MAT4_IDENTITY_INIT;
  size_t i;

  for (i = 0; i < count; i++) {
    olive_mat4_copy(t, mat[i]);
  }
}

void olive_mat4_zero(mat4 mat) {
  __attribute((aligned(16))) mat4 t = OLIVE_MAT4_ZERO_INIT;
  olive_mat4_copy(t, mat);
}

void olive_mat4_pick3(mat4 mat, mat3 dest) {
  dest[0][0] = mat[0][0];
  dest[0][1] = mat[0][1];
  dest[0][2] = mat[0][2];

  dest[1][0] = mat[1][0];
  dest[1][1] = mat[1][1];
  dest[1][2] = mat[1][2];

  dest[2][0] = mat[2][0];
  dest[2][1] = mat[2][1];
  dest[2][2] = mat[2][2];
}

void olive_mat4_pick3t(mat4 mat, mat3 dest) {
  dest[0][0] = mat[0][0];
  dest[0][1] = mat[1][0];
  dest[0][2] = mat[2][0];

  dest[1][0] = mat[0][1];
  dest[1][1] = mat[1][1];
  dest[1][2] = mat[2][1];

  dest[2][0] = mat[0][2];
  dest[2][1] = mat[1][2];
  dest[2][2] = mat[2][2];
}

void olive_mat4_ins3(mat3 mat, mat4 dest) {
  dest[0][0] = mat[0][0];
  dest[0][1] = mat[0][1];
  dest[0][2] = mat[0][2];

  dest[1][0] = mat[1][0];
  dest[1][1] = mat[1][1];
  dest[1][2] = mat[1][2];

  dest[2][0] = mat[2][0];
  dest[2][1] = mat[2][1];
  dest[2][2] = mat[2][2];
}

void olive_mat4_mul(mat4 m1, mat4 m2, mat4 dest) {
  float a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2], a03 = m1[0][3],
        a10 = m1[1][0], a11 = m1[1][1], a12 = m1[1][2], a13 = m1[1][3],
        a20 = m1[2][0], a21 = m1[2][1], a22 = m1[2][2], a23 = m1[2][3],
        a30 = m1[3][0], a31 = m1[3][1], a32 = m1[3][2], a33 = m1[3][3],

        b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2], b03 = m2[0][3],
        b10 = m2[1][0], b11 = m2[1][1], b12 = m2[1][2], b13 = m2[1][3],
        b20 = m2[2][0], b21 = m2[2][1], b22 = m2[2][2], b23 = m2[2][3],
        b30 = m2[3][0], b31 = m2[3][1], b32 = m2[3][2], b33 = m2[3][3];

  dest[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
  dest[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
  dest[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
  dest[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
  dest[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
  dest[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
  dest[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
  dest[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
  dest[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
  dest[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
  dest[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
  dest[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
  dest[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
  dest[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
  dest[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
  dest[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
}

void olive_mat4_mulN(mat4 *__restrict matrices[], uint32_t len, mat4 dest) {
  uint32_t i;
  olive_mat4_mul(*matrices[0], *matrices[1], dest);

  for (i = 2; i < len; i++)
    olive_mat4_mul(dest, *matrices[i], dest);
}

void olive_mat4_mulv(mat4 m, vec4 v, vec4 dest) {
  vec4 res;
  res[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
  res[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
  res[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
  res[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
  olive_vec4_copy(res, dest);
}

float olive_mat4_trace(mat4 m) { return m[0][0] + m[1][1] + m[2][2] + m[3][3]; }

float olive_mat4_trace3(mat4 m) { return m[0][0] + m[1][1] + m[2][2]; }

void olive_mat4_quat(mat4 m, versor dest) {
  float trace, r, rinv;

  trace = m[0][0] + m[1][1] + m[2][2];
  if (trace >= 0.0f) {
    r = sqrtf(1.0f + trace);
    rinv = 0.5f / r;

    dest[0] = rinv * (m[1][2] - m[2][1]);
    dest[1] = rinv * (m[2][0] - m[0][2]);
    dest[2] = rinv * (m[0][1] - m[1][0]);
    dest[3] = r * 0.5f;
  } else if (m[0][0] >= m[1][1] && m[0][0] >= m[2][2]) {
    r = sqrtf(1.0f - m[1][1] - m[2][2] + m[0][0]);
    rinv = 0.5f / r;

    dest[0] = r * 0.5f;
    dest[1] = rinv * (m[0][1] + m[1][0]);
    dest[2] = rinv * (m[0][2] + m[2][0]);
    dest[3] = rinv * (m[1][2] - m[2][1]);
  } else if (m[1][1] >= m[2][2]) {
    r = sqrtf(1.0f - m[0][0] - m[2][2] + m[1][1]);
    rinv = 0.5f / r;

    dest[0] = rinv * (m[0][1] + m[1][0]);
    dest[1] = r * 0.5f;
    dest[2] = rinv * (m[1][2] + m[2][1]);
    dest[3] = rinv * (m[2][0] - m[0][2]);
  } else {
    r = sqrtf(1.0f - m[0][0] - m[1][1] + m[2][2]);
    rinv = 0.5f / r;

    dest[0] = rinv * (m[0][2] + m[2][0]);
    dest[1] = rinv * (m[1][2] + m[2][1]);
    dest[2] = r * 0.5f;
    dest[3] = rinv * (m[0][1] - m[1][0]);
  }
}

void olive_mat4_mulv3(mat4 m, vec3 v, float last, vec3 dest) {
  vec4 res;
  olive_vec4(v, last, res);
  olive_mat4_mulv(m, res, res);
  olive_vec3(res, dest);
}

void olive_mat4_transpose_to(mat4 m, mat4 dest) {
  dest[0][0] = m[0][0];
  dest[1][0] = m[0][1];
  dest[0][1] = m[1][0];
  dest[1][1] = m[1][1];
  dest[0][2] = m[2][0];
  dest[1][2] = m[2][1];
  dest[0][3] = m[3][0];
  dest[1][3] = m[3][1];
  dest[2][0] = m[0][2];
  dest[3][0] = m[0][3];
  dest[2][1] = m[1][2];
  dest[3][1] = m[1][3];
  dest[2][2] = m[2][2];
  dest[3][2] = m[2][3];
  dest[2][3] = m[3][2];
  dest[3][3] = m[3][3];
}

void olive_mat4_transpose(mat4 m) {
  mat4 d;
  olive_mat4_transpose_to(m, d);
  olive_mat4_ucopy(d, m);
}

void olive_mat4_scale_p(mat4 m, float s) {
  m[0][0] *= s;
  m[0][1] *= s;
  m[0][2] *= s;
  m[0][3] *= s;
  m[1][0] *= s;
  m[1][1] *= s;
  m[1][2] *= s;
  m[1][3] *= s;
  m[2][0] *= s;
  m[2][1] *= s;
  m[2][2] *= s;
  m[2][3] *= s;
  m[3][0] *= s;
  m[3][1] *= s;
  m[3][2] *= s;
  m[3][3] *= s;
}

void olive_mat4_scale(mat4 m, float s) { olive_mat4_scale_p(m, s); }

float olive_mat4_det(mat4 mat) {
  float t[6];
  float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
        e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
        i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
        m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3];

  t[0] = k * p - o * l;
  t[1] = j * p - n * l;
  t[2] = j * o - n * k;
  t[3] = i * p - m * l;
  t[4] = i * o - m * k;
  t[5] = i * n - m * j;

  return a * (f * t[0] - g * t[1] + h * t[2]) -
         b * (e * t[0] - g * t[3] + h * t[4]) +
         c * (e * t[1] - f * t[3] + h * t[5]) -
         d * (e * t[2] - f * t[4] + g * t[5]);
}

void olive_mat4_inv(mat4 mat, mat4 dest) {
  float t[6];
  float det;
  float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
        e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
        i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
        m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3];

  t[0] = k * p - o * l;
  t[1] = j * p - n * l;
  t[2] = j * o - n * k;
  t[3] = i * p - m * l;
  t[4] = i * o - m * k;
  t[5] = i * n - m * j;

  dest[0][0] = f * t[0] - g * t[1] + h * t[2];
  dest[1][0] = -(e * t[0] - g * t[3] + h * t[4]);
  dest[2][0] = e * t[1] - f * t[3] + h * t[5];
  dest[3][0] = -(e * t[2] - f * t[4] + g * t[5]);

  dest[0][1] = -(b * t[0] - c * t[1] + d * t[2]);
  dest[1][1] = a * t[0] - c * t[3] + d * t[4];
  dest[2][1] = -(a * t[1] - b * t[3] + d * t[5]);
  dest[3][1] = a * t[2] - b * t[4] + c * t[5];

  t[0] = g * p - o * h;
  t[1] = f * p - n * h;
  t[2] = f * o - n * g;
  t[3] = e * p - m * h;
  t[4] = e * o - m * g;
  t[5] = e * n - m * f;

  dest[0][2] = b * t[0] - c * t[1] + d * t[2];
  dest[1][2] = -(a * t[0] - c * t[3] + d * t[4]);
  dest[2][2] = a * t[1] - b * t[3] + d * t[5];
  dest[3][2] = -(a * t[2] - b * t[4] + c * t[5]);

  t[0] = g * l - k * h;
  t[1] = f * l - j * h;
  t[2] = f * k - j * g;
  t[3] = e * l - i * h;
  t[4] = e * k - i * g;
  t[5] = e * j - i * f;

  dest[0][3] = -(b * t[0] - c * t[1] + d * t[2]);
  dest[1][3] = a * t[0] - c * t[3] + d * t[4];
  dest[2][3] = -(a * t[1] - b * t[3] + d * t[5]);
  dest[3][3] = a * t[2] - b * t[4] + c * t[5];

  det = 1.0f /
        (a * dest[0][0] + b * dest[1][0] + c * dest[2][0] + d * dest[3][0]);

  olive_mat4_scale_p(dest, det);
}

void olive_mat4_inv_fast(mat4 mat, mat4 dest) { olive_mat4_inv(mat, dest); }

void olive_mat4_swap_col(mat4 mat, int col1, int col2) {
  __attribute((aligned(16))) vec4 tmp;
  olive_vec4_copy(mat[col1], tmp);
  olive_vec4_copy(mat[col2], mat[col1]);
  olive_vec4_copy(tmp, mat[col2]);
}

void olive_mat4_swap_row(mat4 mat, int row1, int row2) {
  __attribute((aligned(16))) vec4 tmp;
  tmp[0] = mat[0][row1];
  tmp[1] = mat[1][row1];
  tmp[2] = mat[2][row1];
  tmp[3] = mat[3][row1];

  mat[0][row1] = mat[0][row2];
  mat[1][row1] = mat[1][row2];
  mat[2][row1] = mat[2][row2];
  mat[3][row1] = mat[3][row2];

  mat[0][row2] = tmp[0];
  mat[1][row2] = tmp[1];
  mat[2][row2] = tmp[2];
  mat[3][row2] = tmp[3];
}

float olive_mat4_rmc(vec4 r, mat4 m, vec4 c) {
  vec4 tmp;
  olive_mat4_mulv(m, c, tmp);
  return olive_vec4_dot(r, tmp);
}
