#include "olive/math/mat2.h"
#include "olive/math/vec2.h"
#include "olive/math/vec4.h"
#include "olive/types.h"

void olive_mat2_copy(mat2 mat, mat2 dest) { olive_vec4_ucopy(mat[0], dest[0]); }

void olive_mat2_identity(mat2 mat) {
  __attribute((aligned(16))) mat2 t = MAT2_IDENTITY_INIT;
  olive_mat2_copy(t, mat);
}

void olive_mat2_identity_array(mat2 *__restrict mat, size_t count) {
  __attribute((aligned(16))) mat2 t = MAT2_IDENTITY_INIT;
  size_t i;
  for (i = 0; i < count; i++) {
    olive_mat2_copy(t, mat[i]);
  }
}

void olive_mat2_zero(mat2 mat) {
  __attribute((aligned(16))) mat2 t = MAT2_ZERO_INIT;
  olive_mat2_copy(t, mat);
}

void olive_mat2_mul(mat2 m1, mat2 m2, mat2 dest) {
  float a00 = m1[0][0], a01 = m1[0][1], a10 = m1[1][0], a11 = m1[1][1],
        b00 = m2[0][0], b01 = m2[0][1], b10 = m2[1][0], b11 = m2[1][1];

  dest[0][0] = a00 * b00 + a10 * b01;
  dest[0][1] = a01 * b00 + a11 * b01;
  dest[1][0] = a00 * b10 + a10 * b11;
  dest[1][1] = a01 * b10 + a11 * b11;
}

void olive_mat2_transpose_to(mat2 m, mat2 dest) {
  dest[0][0] = m[0][0];
  dest[0][1] = m[1][0];
  dest[1][0] = m[0][1];
  dest[1][1] = m[1][1];
}

void olive_mat2_transpose(mat2 m) {
  float tmp;
  tmp = m[0][1];
  m[0][1] = m[1][0];
  m[1][0] = tmp;
}

void olive_mat2_mulv(mat2 m, vec2 v, vec2 dest) {
  dest[0] = m[0][0] * v[0] + m[1][0] * v[1];
  dest[1] = m[0][1] * v[0] + m[1][1] * v[1];
}

float olive_mat2_trace(mat2 m) { return m[0][0] + m[1][1]; }

void olive_mat2_scale(mat2 m, float s) {
  m[0][0] = m[0][0] * s;
  m[0][1] = m[0][1] * s;
  m[1][0] = m[1][0] * s;
  m[1][1] = m[1][1] * s;
}

float olive_mat2_det(mat2 mat) {
  return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
}

void olive_mat2_inv(mat2 mat, mat2 dest) {
  float det;
  float a = mat[0][0], b = mat[0][1], c = mat[1][0], d = mat[1][1];

  det = 1.0f / (a * d - b * c);

  dest[0][0] = d * det;
  dest[0][1] = -b * det;
  dest[1][0] = -c * det;
  dest[1][1] = a * det;
}

void olive_mat2_swap_col(mat2 mat, int col1, int col2) {
  float a, b;

  a = mat[col1][0];
  b = mat[col1][1];

  mat[col1][0] = mat[col2][0];
  mat[col1][1] = mat[col2][1];

  mat[col2][0] = a;
  mat[col2][1] = b;
}

void olive_mat2_swap_row(mat2 mat, int row1, int row2) {
  float a, b;

  a = mat[0][row1];
  b = mat[1][row1];

  mat[0][row1] = mat[0][row2];
  mat[1][row1] = mat[1][row2];

  mat[0][row2] = a;
  mat[1][row2] = b;
}

float olive_mat2_rmc(vec2 r, mat2 m, vec2 c) {
  vec2 tmp;
  olive_mat2_mulv(m, c, tmp);
  return olive_vec2_dot(r, tmp);
}
