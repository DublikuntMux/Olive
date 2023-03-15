#ifndef OLIVE_MAT2_H
#define OLIVE_MAT2_H

#include "olive/types.h"

#define MAT2_IDENTITY_INIT                                                     \
  {                                                                            \
    {1.0f, 0.0f}, { 0.0f, 1.0f }                                               \
  }
#define MAT2_ZERO_INIT                                                         \
  {                                                                            \
    {0.0f, 0.0f}, { 0.0f, 0.0f }                                               \
  }

#define MAT2_IDENTITY ((mat2)MAT2_IDENTITY_INIT)
#define MAT2_ZERO ((mat2)MAT2_ZERO_INIT)

void olive_mat2_copy(mat2 mat, mat2 dest);
void olive_mat2_identity(mat2 mat);
void olive_mat2_identity_array(mat2 *__restrict mat, size_t count);
void olive_mat2_zero(mat2 mat);
void olive_mat2_mul(mat2 m1, mat2 m2, mat2 dest);
void olive_mat2_transpose_to(mat2 m, mat2 dest);
void olive_mat2_transpose(mat2 m);
void olive_mat2_mulv(mat2 m, vec2 v, vec2 dest);
float olive_mat2_trace(mat2 m);
void olive_mat2_scale(mat2 m, float s);
float olive_mat2_det(mat2 mat);
void olive_mat2_inv(mat2 mat, mat2 dest);
void olive_mat2_swap_col(mat2 mat, int col1, int col2);
void olive_mat2_swap_row(mat2 mat, int row1, int row2);
float olive_mat2_rmc(vec2 r, mat2 m, vec2 c);

#endif // OLIVE_MAT2_H
