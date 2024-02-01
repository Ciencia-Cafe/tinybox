// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "os.h"
#include "render.h"
#include "opengl.h"
#include "common.h"
#define STBI_NO_THREAD_LOCALS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

INCBIN(general_vs_src, "src/shaders/general_vs.glsl");
INCBIN(general_fs_src, "src/shaders/general_fs.glsl");

static uint32_t compile_shader(const char *src, uint32_t kind);
static uint32_t compile_shader_src(const char *vs, const char *fs);
static inline Vertex make_v(float x, float y, float u, float v);

#define MAX_QUADS (1 << 14)
#define MAX_VERTS (MAX_QUADS * 4)
#define MAX_INDXS (MAX_QUADS * 6)

static struct
{
	uint32_t  vao;
	uint32_t  vbo;
	uint32_t  ebo;
	uint32_t  shader;

	mat4      proj;
	mat4      view;

	Image     pixel;
	Image     hot_image;
	Color     hot_color;

	Vertex    vertices[MAX_VERTS];
	uint32_t  curr_vert;
	uint32_t  curr_quad;
}
self = { 0 };

void render_init() {
	// Create the pixel image
	self.pixel = render_mem_image(1, 1, (uint8_t[]){255, 255, 255, 255});
	render_set_image(self.pixel);

	// Default color as white
	self.hot_color = WHITE;

	// Create the vertex array object
	glGenVertexArrays(1, &self.vao);
	glBindVertexArray(self.vao);

	// Create the vertex buffer object
	glGenBuffers(1, &self.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, self.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(self.vertices), NULL, GL_DYNAMIC_DRAW);

	// NOTE(ellora):
	// Indices are allways the same, so we can just set them once.
	uint32_t indxs[MAX_INDXS];
	for (uint32_t v = 0, i = 0; i < MAX_INDXS; i+= 6, v+= 4)  {
		indxs[i + 0] = v + 0;
		indxs[i + 1] = v + 1;
		indxs[i + 2] = v + 2;
		indxs[i + 3] = v + 0;
		indxs[i + 4] = v + 2;
		indxs[i + 5] = v + 3;
	}
	glGenBuffers(1, &self.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indxs), indxs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Compiling shaders
	self.shader = compile_shader_src(
		incbin_general_vs_src_start,
		incbin_general_fs_src_start);
	assert(self.shader != 0);
}

void render_frame() {
	vec2 w_size = os_window_size();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, w_size.x, w_size.y);
}

void render_flush() {
	// Bind the vertex array object
	glBindVertexArray(self.vao);

	// Update the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, self.vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, self.curr_vert * sizeof(Vertex), self.vertices);

	// Setup attributes
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glVertexAttribPointer(ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(ATTRIB_COLOR);
	glVertexAttribPointer(ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(ATTRIB_TEXCOORDS);
	glVertexAttribPointer(ATTRIB_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Draw the quads
	glUseProgram(self.shader);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.ebo);
	glBindTexture(GL_TEXTURE_2D, self.hot_image.id);
	glDrawElements(GL_TRIANGLES, self.curr_quad * 6, GL_UNSIGNED_INT, 0);

	// Reset stuff
	self.curr_quad = 0;
	self.curr_vert = 0;
}

void render_set_color(Color c) {
	self.hot_color = c;
}

void render_set_image(Image i) {
	self.hot_image = i;
}

// Load image from file using stb image
Image render_load_image(const char *filename) {
	int32_t w, h, n;
	uint8_t *pixels = stbi_load(filename, &w, &h, &n, 4); // Force RGBA
	if (pixels == NULL) {
		os_panic("Could't load image");
	}
	Image img = render_mem_image(w, h, pixels);
	stbi_image_free(pixels);

	return img;
}

Image render_mem_image(int32_t width, int32_t height, const uint8_t *pixels) {
	Image img = { .id = 0, .width = width, .height = height };

	glGenTextures(1, &img.id);
	glBindTexture(GL_TEXTURE_2D, img.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return img;
}

void render_push_rec(float x, float y, float w, float h, float u0, float u1, float v0, float v1) {
	if (self.curr_quad >= MAX_QUADS) {
		render_flush();
	}

	self.vertices[self.curr_vert++] = make_v(x, y, u0, v0);
	self.vertices[self.curr_vert++] = make_v(x + w, y, u1, v0);
	self.vertices[self.curr_vert++] = make_v(x + w, y + h, u1, v1);
	self.vertices[self.curr_vert++] = make_v(x, y + h, u0, v1);

	self.curr_quad++;
}

// sugar dummy bunny way to create a vertex (because is pretty anoying write it manually)
Vertex make_v(float x, float y, float u, float v) {
	return (Vertex) {
		x, y, self.hot_color.r, self.hot_color.g,
		self.hot_color.b, self.hot_color.a, u, v };
}

uint32_t compile_shader(const char *src, uint32_t kind) {
	uint32_t shader = glCreateShader(kind);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// Getting the result of compiling process
	int32_t success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		glDeleteShader(shader);
		printf("[ERROR] %s\n", infoLog);
		return 0;
	}

	return shader;
}

uint32_t compile_shader_src(const char *vs, const char *fs) {
	uint32_t vertexShader = compile_shader(vs, GL_VERTEX_SHADER);
	uint32_t fragmentShader = compile_shader(fs, GL_FRAGMENT_SHADER);

	uint32_t program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Get compile result status
	int32_t success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		glDeleteProgram(program);
		printf("[ERROR] %s\n", infoLog);
		return 0;
	}

	return program;
}
