// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#ifndef TINYBOX_RENDER_H
#define TINYBOX_RENDER_H

#include "math.h"
#include <inttypes.h>

#define WHITE (Color){1.0f, 1.0f, 1.0f, 1.0f}
#define BLACK (Color){0.0f, 0.0f, 0.0f, 1.0f}

typedef struct { float r, g, b, a; } Color;

#define ATTRIB_POSITION   0
#define ATTRIB_COLOR      1
#define ATTRIB_TEXCOORDS  2

typedef struct
{
	float x, y;
	float u, v;
	float r, g, b, a;
}
Vertex;

typedef struct
{
	uint32_t id;
	int32_t width;
	int32_t height;
}
Image;

void render_init();
void render_frame();
void render_flush();

void render_set_image(Image i);
void render_set_color(Color c);

void render_push_mat4();
void render_pop_mat4();
void render_translate(float x, float y);
void render_scale(float sx, float sy);
void render_rotate(float r);

Image render_load_image(const char *filename); 
Image render_mem_image(int32_t width, int32_t height, const uint8_t *pixels);

void render_push_rec(float x, float y, float w, float h, float u0, float u1, float v0, float v1);

#endif