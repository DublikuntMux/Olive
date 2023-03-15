#ifndef OLIVE_MAT3_H
#define OLIVE_MAT3_H

#include "olive/types.h"

#define MAT3_IDENTITY_INIT                                                     \
  {                                                                            \
    {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f }               \
  }
#define MAT3_ZERO_INIT                                                         \
  {                                                                            \
    {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f }               \
  }

#define MAT3_IDENTITY ((mat3)olive_MAT3_IDENTITY_INIT)
#define MAT3_ZERO ((mat3)olive_MAT3_ZERO_INIT)

void olive_mat3_copy(mat3 mat, mat3 dest);
void olive_mat3_identity(mat3 mat);
void olive_mat3_identity_array(mat3 *__restrict mat, size_t count);
void olive_mat3_zero(mat3 mat);
void olive_mat3_mul(mat3 m1, mat3 m2, mat3 dest);
void olive_mat3_transpose_to(mat3 m, mat3 dest);
void olive_mat3_transpose(mat3 m);
void olive_mat3_mulv(mat3 m, vec3 v, vec3 dest);
float olive_mat3_trace(mat3 m);
void olive_mat3_quat(mat3 m, versor dest);
void olive_mat3_scale(mat3 m, float s);
float olive_mat3_det(mat3 mat);
void olive_mat3_inv(mat3 mat, mat3 dest);
void olive_mat3_swap_col(mat3 mat, int col1, int col2);
void olive_mat3_swap_row(mat3 mat, int row1, int row2);
float olive_mat3_rmc(vec3 r, mat3 m, vec3 c);

#endif // OLIVE_MAT3_H
