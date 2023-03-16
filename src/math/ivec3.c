#include "olive/types.h"
#include <math.h>
#include <stdlib.h>

void olive_ivec3(ivec4 v4, ivec3 dest) {
	dest[0] = v4[0];
	dest[1] = v4[1];
	dest[2] = v4[2];
}

void olive_ivec3_copy(ivec3 a, ivec3 dest) {
	dest[0] = a[0];
	dest[1] = a[1];
	dest[2] = a[2];
}

void olive_ivec3_zero(ivec3 v) { v[0] = v[1] = v[2] = 0; }

void olive_ivec3_one(ivec3 v) { v[0] = v[1] = v[2] = 1; }

void olive_ivec3_add(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
}

void olive_ivec3_adds(ivec3 v, int s, ivec3 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
}

void olive_ivec3_sub(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
}

void olive_ivec3_subs(ivec3 v, int s, ivec3 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
}

void olive_ivec3_mul(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
}

void olive_ivec3_scale(ivec3 v, int s, ivec3 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
	dest[2] = v[2] * s;
}

int olive_ivec3_distance2(ivec3 a, ivec3 b) {
	int xd, yd, zd;
	xd = a[0] - b[0];
	yd = a[1] - b[1];
	zd = a[2] - b[2];
	return xd * xd + yd * yd + zd * zd;
}

float olive_ivec3_distance(ivec3 a, ivec3 b) {
	return sqrtf((float)olive_ivec3_distance2(a, b));
}

void olive_ivec3_maxv(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] > b[0] ? a[0] : b[0];
	dest[1] = a[1] > b[1] ? a[1] : b[1];
	dest[2] = a[2] > b[2] ? a[2] : b[2];
}

void olive_ivec3_minv(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] < b[0] ? a[0] : b[0];
	dest[1] = a[1] < b[1] ? a[1] : b[1];
	dest[2] = a[2] < b[2] ? a[2] : b[2];
}

void olive_ivec3_clamp(ivec3 v, int minVal, int maxVal) {
	if (v[0] < minVal) {
		v[0] = minVal;
	} else if (v[0] > maxVal) {
		v[0] = maxVal;
	}

	if (v[1] < minVal) {
		v[1] = minVal;
	} else if (v[1] > maxVal) {
		v[1] = maxVal;
	}

	if (v[2] < minVal) {
		v[2] = minVal;
	} else if (v[2] > maxVal) {
		v[2] = maxVal;
	}
}

void olive_ivec3_abs(ivec3 v, ivec3 dest) {
	dest[0] = abs(v[0]);
	dest[1] = abs(v[1]);
	dest[2] = abs(v[2]);
}
