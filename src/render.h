// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#ifndef TINYBOX_RENDER_H
#define TINYBOX_RENDER_H

#include "math.h"
#include <inttypes.h>

#define ATTRIB_POSITION   0
#define ATTRIB_TEXCOORDS  1
#define ATTRIB_COLOR      2
#define ATTRIB_NORMAL     3

typedef struct
{
	float x, y;
	float u, v;
	float r, g, b, a;
}
Vertex;

typedef struct
{
	mat4     model_matrix;
	Vertex   *vertices;
	uint32_t buffer_id;

	// TODO(ellora): Material
	// TODO(ellora): Is dirty?
}
Mesh;

void render_init();
void render_mesh(Mesh *m);
void render_pass();

#endif