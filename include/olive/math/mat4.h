#ifndef OLIVE_MAT4_H
#define OLIVE_MAT4_H

#include "olive/types.h"

#define OLIVE_MAT4_IDENTITY_INIT                                               \
  {                                                                            \
    {1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f},                        \
        {0.0f, 0.0f, 1.0f, 0.0f}, {                                            \
      0.0f, 0.0f, 0.0f, 1.0f                                                   \
    }                                                                          \
  }

#define OLIVE_MAT4_ZERO_INIT                                                   \
  {                                                                            \
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},                        \
        {0.0f, 0.0f, 0.0f, 0.0f}, {                                            \
      0.0f, 0.0f, 0.0f, 0.0f                                                   \
    }                                                                          \
  }

#define OLIVE_MAT4_IDENTITY ((mat4)OLIVE_MAT4_IDENTITY_INIT)
#define OLIVE_MAT4_ZERO ((mat4)OLIVE_MAT4_ZERO_INIT)

void olive_mat4_ucopy(mat4 mat, mat4 dest);
void olive_mat4_copy(mat4 mat, mat4 dest);
void olive_mat4_identity(mat4 mat);
void olive_mat4_identity_array(mat4 *__restrict mat, size_t count);
void olive_mat4_zero(mat4 mat);
void olive_mat4_pick3(mat4 mat, mat3 dest);
void olive_mat4_pick3t(mat4 mat, mat3 dest);
void olive_mat4_ins3(mat3 mat, mat4 dest);
void olive_mat4_mul(mat4 m1, mat4 m2, mat4 dest);
void olive_mat4_mulN(mat4 *__restrict matrices[], uint32_t len, mat4 dest);
void olive_mat4_mulv(mat4 m, vec4 v, vec4 dest);
float olive_mat4_trace(mat4 m);
float olive_mat4_trace3(mat4 m);
void olive_mat4_quat(mat4 m, versor dest);
void olive_mat4_mulv3(mat4 m, vec3 v, float last, vec3 dest);
void olive_mat4_transpose_to(mat4 m, mat4 dest);
void olive_mat4_transpose(mat4 m);
void olive_mat4_scale_p(mat4 m, float s);
void olive_mat4_scale(mat4 m, float s);
float olive_mat4_det(mat4 mat);
void olive_mat4_inv(mat4 mat, mat4 dest);
void olive_mat4_inv_fast(mat4 mat, mat4 dest);
void olive_mat4_swap_col(mat4 mat, int col1, int col2);
void olive_mat4_swap_row(mat4 mat, int row1, int row2);
float olive_mat4_rmc(vec4 r, mat4 m, vec4 c);

#endif // OLIVE_MAT3_H
