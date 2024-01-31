// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "render.h"
#include "opengl.h"
#include "common.h"
#include <stdio.h>
#include <inttypes.h>

INCBIN(general_vs_src, "src/shaders/general_vs.glsl");
INCBIN(general_fs_src, "src/shaders/general_fs.glsl");

static uint32_t compile_shader(const char *src, uint32_t kind);
static uint32_t compile_shader_src(const char *vs, const char *fs);

uint32_t shader;
uint32_t vbo_test, vao_test;

void render_init() {
	shader = compile_shader_src(
		incbin_general_vs_src_start,
		incbin_general_fs_src_start);

	// Create a triangle for testing
	glCreateBuffers(1, &vbo_test);
	glCreateVertexArrays(1, &vao_test);
	glBindVertexArray(vao_test);

	float vertices[] = {
		-0.5f, -0.5f,  1.0, 0.0, 0.0, 1.0,  0.0, 0.0,
		 0.5f, -0.5f,  0.0, 1.0, 0.0, 1.0,  0.0, 0.0,
		 0.0f,  0.5f,  0.0, 0.0, 1.0, 1.0,  0.0, 0.0,
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo_test);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void render_pass() {
	glViewport(0, 0, 800, 600);
	glClearColor(0.1f, 0.2f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
