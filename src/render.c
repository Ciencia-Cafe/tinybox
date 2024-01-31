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

void render_init() {
	uint32_t shader = compile_shader_src(
		incbin_general_vs_src_start,
		incbin_general_fs_src_start);
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
