#define SOURCE_VS                          \
"#version 330 core\n"                      \
"layout (location = 0) in vec2 a_pos;"     \
"layout (location = 1) in vec4 a_color;"   \
"layout (location = 2) in vec2 a_uv;"      \
"out vec4 color;"                          \
"out vec2 uv;"                             \
"void main() {"                            \
"   gl_Position = vec4(a_pos, 0.0, 1.0);"  \
"   color = a_color;"                      \
"   uv = a_uv;"                            \
"}"

#define SOURCE_FS           \
"#version 330 core\n"       \
"out vec4 colour;"          \
"in vec4 color;"            \
"in vec2 uv;"               \
"void main() {"             \
"    colour = vec4(color);" \
"}"

static uint32_t igfx_load_shader(const char *src, uint32_t type); 
static uint32_t igfx_load_program(const char *vs, const char *fs);

#define MAX_QUADS (1 << 14)
#define MAX_VERTS (MAX_QUADS * 4)
#define MAX_INDXS (MAX_QUADS * 6)

uint32_t shader;
uint32_t vbo_test, vao_test;


void gfx_init() {
	shader = igfx_load_program(SOURCE_VS, SOURCE_FS);

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

	// TODO(ellora): Move to logging system
	printf("[LOG] %s\n", glGetString(GL_VERSION));
}

void gfx_begin() {
	glViewport(0, 0, 800, 600);
	glClearColor(0.1f, 0.2f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	vec2 win_size = os_window_size();
	glViewport(0, 0, win_size.x, win_size.y);
}

void gfx_end() {
	glUseProgram(shader);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

uint32_t igfx_load_shader(const char *src, uint32_t type) {
	uint32_t shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int32_t success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("[ERROR] %s\n", infoLog);
	}

	return shader;
}

uint32_t igfx_load_program(const char *vs, const char *fs) {
	uint32_t vertexShader = igfx_load_shader(vs, GL_VERTEX_SHADER);
	uint32_t fragmentShader = igfx_load_shader(fs, GL_FRAGMENT_SHADER);

	uint32_t program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int32_t success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("[ERROR] %s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}