// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#ifndef TINYBOX_RENDER_H
#define TINYBOX_RENDER_H

#include "math.h"
#include "stb_truetype.h"
#include <inttypes.h>

#define WHITE (Color){1.0f, 1.0f, 1.0f, 1.0f}
#define BLACK (Color){0.0f, 0.0f, 0.0f, 1.0f}

typedef struct { float r, g, b, a; } Color;

typedef struct
{
	uint32_t id;
	int32_t  width;
	int32_t  height;
}
Image;

typedef struct
{
	Image            atlas;
	// We need a new set for each alphabet
	// this font supports it.
	stbtt_bakedchar *glyphs;
	stbtt_fontinfo   stbfont;
}
Font;

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

Font *render_load_font(const char *filename, int32_t size);
Image render_load_image(const char *filename); 
Image render_mem_image(int32_t width, int32_t height, const uint8_t *pixels);

void render_push_quad(float x1, float y1, float x2, float y2, float u0, float u1, float v0, float v1);

#endif