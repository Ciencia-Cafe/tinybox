#ifndef OPENGL_H
#define OPENGL_H

#include <inttypes.h>

#define GL_FALSE 0
#define GL_TRUE 1
#define GL_FLOAT 0x1406
#define GL_UNSIGNED_BYTE 0x1401
#define GL_RGBA 0x1908
#define GL_RGBA8 0x8058
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_DEPTH_TEST 0x0B71
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_NEAREST 0x2600
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_REPEAT 0x2901
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_BLEND 0x0BE2
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_TRIANGLES 0x0004
#define GL_LINK_STATUS 0x8B82
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#define GL_DEBUG_SEVERITY_HIGH 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#define GL_VERSION 0x1F02
#define GL_COMPILE_STATUS 0x8B81
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4

typedef uint32_t GLenum;
typedef uint32_t GLuint32;
typedef uint8_t GLboolean;
typedef uint32_t GLbitfield;
typedef char GLchar;
typedef int32_t GLint;
typedef int32_t GLsizei;
typedef uint32_t GLuint;
typedef uintptr_t GLsizeiptr;
typedef uintptr_t GLintptr;
typedef float GLfloat;
typedef uint8_t GLubyte;

// OpenGL 1.0 functions
void glEnable(GLenum cap);
void glBlendFunc(GLenum sfactor, GLenum dfactor);
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void glClear(GLbitfield mask);
void glDisable(GLenum cap);
void glDrawArrays(GLenum mode, GLint first, GLsizei count);
const GLubyte *glGetString(GLenum name);

// OpenGL 3.3 functions
typedef void (*PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (*PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags);
typedef void (*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (*PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void (*PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (*PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (*PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (*PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
typedef GLuint (*PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar* const* strings);
typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void (*PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint* pipelines);
typedef void (*PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (*PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (*PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (*PFNGLDEBUGMESSAGECALLBACKPROC)(void* callback, const void* userParam);
typedef void (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (*PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (*PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
typedef void (*PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef GLuint (*PFNGLCREATESHADERPROC)(GLenum type);
typedef void (*PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
typedef void (*PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
typedef void (*PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef GLuint (*PFNGLCREATEPROGRAMPROC)(void);
typedef void (*PFNGLDELETESHADERPROC)(GLuint shader);
typedef void (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (*PFNGLUSEPROGRAMPROC)(GLuint program);



#define GL_FUNCTIONS(X) \
	X(PFNGLCREATEBUFFERSPROC, glCreateBuffers) \
	X(PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage) \
	X(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray) \
	X(PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays) \
	X(PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding) \
	X(PFNGLVERTEXARRAYVERTEXBUFFERPROC, glVertexArrayVertexBuffer) \
	X(PFNGLVERTEXARRAYATTRIBFORMATPROC, glVertexArrayAttribFormat) \
	X(PFNGLENABLEVERTEXARRAYATTRIBPROC, glEnableVertexArrayAttrib) \
	X(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv) \
	X(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog) \
	X(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines) \
	X(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages) \
	X(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline) \
	X(PFNGLPROGRAMUNIFORMMATRIX2FVPROC, glProgramUniformMatrix2fv) \
	X(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback) \
	X(PFNGLATTACHSHADERPROC, glAttachShader) \
	X(PFNGLLINKPROGRAMPROC, glLinkProgram) \
	X(PFNGLSHADERSOURCEPROC, glShaderSource) \
	X(PFNGLCOMPILESHADERPROC, glCompileShader) \
	X(PFNGLCREATESHADERPROC, glCreateShader) \
	X(PFNGLGETSHADERIVPROC, glGetShaderiv) \
	X(PFNGLGETPROGRAMIVPROC, glGetProgramiv) \
	X(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog) \
	X(PFNGLCREATEPROGRAMPROC, glCreateProgram) \
	X(PFNGLDELETESHADERPROC, glDeleteShader) \
	X(PFNGLBINDBUFFERPROC, glBindBuffer) \
	X(PFNGLBUFFERDATAPROC, glBufferData) \
	X(PFNGLGENBUFFERSPROC, glGenBuffers) \
	X(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer) \
	X(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
	X(PFNGLUSEPROGRAMPROC, glUseProgram)

#define X(type, name) type name;
GL_FUNCTIONS(X)
#undef X

#endif
