// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#ifndef TINYBOX_MATH_H
#define TINYBOX_MATH_H

typedef union
{
	struct { float x; float y; };
	struct { float u; float v; };
	float e[2];
}
vec2;

#endif