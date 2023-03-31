#include "olive/math/mat3.h"
#include "olive/math/vec3.h"
#include "olive/types.h"
#include <math.h>

void olive_mat3_copy(mat3 mat, mat3 dest) {
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

void olive_mat3_identity(mat3 mat) {
	__attribute((aligned(16))) mat3 t = MAT3_IDENTITY_INIT;
	olive_mat3_copy(t, mat);
}

void olive_mat3_identity_array(mat3 *__restrict mat, size_t count) {
	__attribute((aligned(16))) mat3 t = MAT3_IDENTITY_INIT;
	size_t i;

	for (i = 0; i < count; i++) {
		olive_mat3_copy(t, mat[i]);
	}
}

void olive_mat3_zero(mat3 mat) {
	__attribute((aligned(16))) mat3 t = MAT3_ZERO_INIT;
	olive_mat3_copy(t, mat);
}

void olive_mat3_mul(mat3 m1, mat3 m2, mat3 dest) {
	float a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2], a10 = m1[1][0],
		  a11 = m1[1][1], a12 = m1[1][2], a20 = m1[2][0], a21 = m1[2][1],
		  a22 = m1[2][2],

		  b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2], b10 = m2[1][0],
		  b11 = m2[1][1], b12 = m2[1][2], b20 = m2[2][0], b21 = m2[2][1],
		  b22 = m2[2][2];

	dest[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
	dest[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
	dest[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
	dest[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
	dest[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
	dest[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
	dest[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
	dest[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
	dest[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
}

void olive_mat3_transpose_to(mat3 m, mat3 dest) {
	dest[0][0] = m[0][0];
	dest[0][1] = m[1][0];
	dest[0][2] = m[2][0];
	dest[1][0] = m[0][1];
	dest[1][1] = m[1][1];
	dest[1][2] = m[2][1];
	dest[2][0] = m[0][2];
	dest[2][1] = m[1][2];
	dest[2][2] = m[2][2];
}

void olive_mat3_transpose(mat3 m) {
	__attribute((aligned(16))) mat3 tmp;

	tmp[0][1] = m[1][0];
	tmp[0][2] = m[2][0];
	tmp[1][0] = m[0][1];
	tmp[1][2] = m[2][1];
	tmp[2][0] = m[0][2];
	tmp[2][1] = m[1][2];

	m[0][1] = tmp[0][1];
	m[0][2] = tmp[0][2];
	m[1][0] = tmp[1][0];
	m[1][2] = tmp[1][2];
	m[2][0] = tmp[2][0];
	m[2][1] = tmp[2][1];
}

void olive_mat3_mulv(mat3 m, vec3 v, vec3 dest) {
	vec3 res;
	res[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2];
	res[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2];
	res[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2];
	olive_vec3_copy(res, dest);
}

float olive_mat3_trace(mat3 m) { return m[0][0] + m[1][1] + m[2][2]; }

void olive_mat3_quat(mat3 m, versor dest) {
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

void olive_mat3_scale(mat3 m, float s) {
	m[0][0] *= s;
	m[0][1] *= s;
	m[0][2] *= s;
	m[1][0] *= s;
	m[1][1] *= s;
	m[1][2] *= s;
	m[2][0] *= s;
	m[2][1] *= s;
	m[2][2] *= s;
}

float olive_mat3_det(mat3 mat) {
	float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[1][0],
		  e = mat[1][1], f = mat[1][2], g = mat[2][0], h = mat[2][1],
		  i = mat[2][2];

	return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}

void olive_mat3_inv(mat3 mat, mat3 dest) {
	float det;
	float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[1][0],
		  e = mat[1][1], f = mat[1][2], g = mat[2][0], h = mat[2][1],
		  i = mat[2][2];

	dest[0][0] = e * i - f * h;
	dest[0][1] = -(b * i - h * c);
	dest[0][2] = b * f - e * c;
	dest[1][0] = -(d * i - g * f);
	dest[1][1] = a * i - c * g;
	dest[1][2] = -(a * f - d * c);
	dest[2][0] = d * h - g * e;
	dest[2][1] = -(a * h - g * b);
	dest[2][2] = a * e - b * d;

	det = 1.0f / (a * dest[0][0] + b * dest[1][0] + c * dest[2][0]);

	olive_mat3_scale(dest, det);
}

void olive_mat3_swap_col(mat3 mat, int col1, int col2) {
	vec3 tmp;
	olive_vec3_copy(mat[col1], tmp);
	olive_vec3_copy(mat[col2], mat[col1]);
	olive_vec3_copy(tmp, mat[col2]);
}

void olive_mat3_swap_row(mat3 mat, int row1, int row2) {
	vec3 tmp;
	tmp[0] = mat[0][row1];
	tmp[1] = mat[1][row1];
	tmp[2] = mat[2][row1];

	mat[0][row1] = mat[0][row2];
	mat[1][row1] = mat[1][row2];
	mat[2][row1] = mat[2][row2];

	mat[0][row2] = tmp[0];
	mat[1][row2] = tmp[1];
	mat[2][row2] = tmp[2];
}

float olive_mat3_rmc(vec3 r, mat3 m, vec3 c) {
	vec3 tmp;
	olive_mat3_mulv(m, c, tmp);
	return olive_vec3_dot(r, tmp);
}
