#include "olive/types.h"
#include <math.h>
#include <stdlib.h>

void olive_ivec4(ivec3 v3, int last, ivec4 dest) {
	dest[0] = v3[0];
	dest[1] = v3[1];
	dest[2] = v3[2];
	dest[3] = last;
}

void olive_ivec4_copy(ivec4 a, ivec4 dest) {
	dest[0] = a[0];
	dest[1] = a[1];
	dest[2] = a[2];
	dest[3] = a[3];
}

void olive_ivec4_zero(ivec4 v) { v[0] = v[1] = v[2] = v[3] = 0; }

void olive_ivec4_one(ivec4 v) { v[0] = v[1] = v[2] = v[3] = 1; }

void olive_ivec4_add(ivec4 a, ivec4 b, ivec4 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
	dest[3] = a[3] + b[3];
}

void olive_ivec4_adds(ivec4 v, int s, ivec4 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
	dest[3] = v[3] + s;
}

void olive_ivec4_sub(ivec4 a, ivec4 b, ivec4 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
	dest[3] = a[3] - b[3];
}

void olive_ivec4_subs(ivec4 v, int s, ivec4 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
	dest[3] = v[3] - s;
}

void olive_ivec4_mul(ivec4 a, ivec4 b, ivec4 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
	dest[3] = a[3] * b[3];
}

void olive_ivec4_scale(ivec4 v, int s, ivec4 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
	dest[2] = v[2] * s;
	dest[3] = v[3] * s;
}

int olive_ivec4_distance2(ivec4 a, ivec4 b) {
	int xd, yd, zd, wd;
	xd = a[0] - b[0];
	yd = a[1] - b[1];
	zd = a[2] - b[2];
	wd = a[3] - b[3];
	return xd * xd + yd * yd + zd * zd + wd * wd;
}

float olive_ivec4_distance(ivec4 a, ivec4 b) {
	return sqrtf((float)olive_ivec4_distance2(a, b));
}

void olive_ivec4_maxv(ivec4 a, ivec4 b, ivec4 dest) {
	dest[0] = a[0] > b[0] ? a[0] : b[0];
	dest[1] = a[1] > b[1] ? a[1] : b[1];
	dest[2] = a[2] > b[2] ? a[2] : b[2];
	dest[3] = a[3] > b[3] ? a[3] : b[3];
}

void olive_ivec4_minv(ivec4 a, ivec4 b, ivec4 dest) {
	dest[0] = a[0] < b[0] ? a[0] : b[0];
	dest[1] = a[1] < b[1] ? a[1] : b[1];
	dest[2] = a[2] < b[2] ? a[2] : b[2];
	dest[3] = a[3] < b[3] ? a[3] : b[3];
}

void olive_ivec4_clamp(ivec4 v, int minVal, int maxVal) {
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

	if (v[3] < minVal) {
		v[3] = minVal;
	} else if (v[3] > maxVal) {
		v[3] = maxVal;
	}
}

void olive_ivec4_abs(ivec4 v, ivec4 dest) {
	dest[0] = abs(v[0]);
	dest[1] = abs(v[1]);
	dest[2] = abs(v[2]);
	dest[3] = abs(v[3]);
}
