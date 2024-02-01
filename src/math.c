// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
// I just stole those functions from Ray

#include "math.h"

// https://github.com/raysan5/raylib/blob/master/src/raymath.h#L1246
mat4 math_mat4_identity() {
	return (mat4){
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };
}

// https://github.com/raysan5/raylib/blob/master/src/raymath.h#L1308
mat4 math_mat4_mul(mat4 a, mat4 b) {
	mat4 result = { 0 };

	result.m0 = a.m0*b.m0 + a.m1*b.m4 + a.m2*b.m8 + a.m3*b.m12;
	result.m1 = a.m0*b.m1 + a.m1*b.m5 + a.m2*b.m9 + a.m3*b.m13;
	result.m2 = a.m0*b.m2 + a.m1*b.m6 + a.m2*b.m10 + a.m3*b.m14;
	result.m3 = a.m0*b.m3 + a.m1*b.m7 + a.m2*b.m11 + a.m3*b.m15;
	result.m4 = a.m4*b.m0 + a.m5*b.m4 + a.m6*b.m8 + a.m7*b.m12;
	result.m5 = a.m4*b.m1 + a.m5*b.m5 + a.m6*b.m9 + a.m7*b.m13;
	result.m6 = a.m4*b.m2 + a.m5*b.m6 + a.m6*b.m10 + a.m7*b.m14;
	result.m7 = a.m4*b.m3 + a.m5*b.m7 + a.m6*b.m11 + a.m7*b.m15;
	result.m8 = a.m8*b.m0 + a.m9*b.m4 + a.m10*b.m8 + a.m11*b.m12;
	result.m9 = a.m8*b.m1 + a.m9*b.m5 + a.m10*b.m9 + a.m11*b.m13;
	result.m10 = a.m8*b.m2 + a.m9*b.m6 + a.m10*b.m10 + a.m11*b.m14;
	result.m11 = a.m8*b.m3 + a.m9*b.m7 + a.m10*b.m11 + a.m11*b.m15;
	result.m12 = a.m12*b.m0 + a.m13*b.m4 + a.m14*b.m8 + a.m15*b.m12;
	result.m13 = a.m12*b.m1 + a.m13*b.m5 + a.m14*b.m9 + a.m15*b.m13;
	result.m14 = a.m12*b.m2 + a.m13*b.m6 + a.m14*b.m10 + a.m15*b.m14;
	result.m15 = a.m12*b.m3 + a.m13*b.m7 + a.m14*b.m11 + a.m15*b.m15;

	return result;
}

// https://github.com/raysan5/raylib/blob/master/src/raymath.h#L1587
mat4 math_mat4_ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 result = { 0 };

	result.m0 = 2.0f / (right - left);
	result.m5 = 2.0f / (top - bottom);
	result.m10 = -2.0f / (far - near);
	result.m12 = -(right + left)/(right - left);
	result.m13 = -(top + bottom)/(top - bottom);
	result.m14 = -(far + near)/(far - near);
	result.m15 = 1.0f;

	return result;
}


