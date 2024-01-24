#ifndef OPENGL_H
#define OPENGL_H

#include <inttypes.h>

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef char GLchar;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLuint;
typedef uintptr_t GLsizeiptr;
typedef uintptr_t GLintptr;
typedef float GLfloat;

#define GL_DEBUG_SEVERITY_HIGH 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_FLOAT 0x1406
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_NEAREST 0x2600
#define GL_LINK_STATUS 0x8B82
#define GL_FRAGMENT_SHADER_BIT 0x00000002
#define GL_VERTEX_SHADER_BIT 0x00000001
#define GL_BLEND 0x0BE2
#define GL_SRC_ALPHA 0x0302
#define GL_DEPTH_TEST 0x0B71
#define GL_CULL_FACE 0x0B44
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_REPEAT 0x2901
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_UNSIGNED_BYTE 0x1401
#define GL_RGBA 0x1908
#define GL_TRIANGLES 0x0004
#define GL_RGBA8 0x8058
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_STENCIL_BUFFER_BIT 0x00000400

typedef void (* PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (* PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags);
typedef void (* PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (* PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void (* PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (* PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (* PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (* PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
typedef GLuint(* PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar* const* strings);
typedef void (* PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
typedef void (* PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void (* PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint* pipelines);
typedef void (* PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (* PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (* PFNGLBINDTEXTUREUNITPROC)(GLuint unit, GLuint texture);
typedef void (* PFNGLCREATETEXTURESPROC)(GLenum target, GLsizei n, GLuint* textures);
typedef void (* PFNGLTEXTUREPARAMETERIPROC)(GLuint texture, GLenum pname, GLint param);
typedef void (* PFNGLTEXTURESTORAGE2DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (* PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
typedef void (* PFNGLDEBUGMESSAGECALLBACKPROC)(void* callback, const void* userParam);
typedef void (* PFNGLENABLEPROC)(GLenum cap);
typedef void (* PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (* PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (* PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (* PFNGLCLEARPROC)(GLbitfield mask);
typedef void (* PFNGLDISABLEPROC)(GLenum cap);
typedef void (* PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);

// OpenGL 1.0 functions
PFNGLENABLEPROC     glEnable(GLenum cap);
PFNGLBLENDFUNCPROC  glBlendFunc(GLenum sfactor, GLenum dfactor);
PFNGLVIEWPORTPROC   glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCLEARCOLORPROC glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCLEARPROC      glClear(GLbitfield mask);
PFNGLDISABLEPROC    glDisable(GLenum cap);
PFNGLDRAWARRAYSPROC glDrawArrays(GLenum mode, GLint first, GLsizei count);

// Functions to be loaded
#define GL_FUNCTIONS(X) \
	X(PFNGLCREATEBUFFERSPROC,            glCreateBuffers            ) \
	X(PFNGLNAMEDBUFFERSTORAGEPROC,       glNamedBufferStorage       ) \
	X(PFNGLBINDVERTEXARRAYPROC,          glBindVertexArray          ) \
	X(PFNGLCREATEVERTEXARRAYSPROC,       glCreateVertexArrays       ) \
	X(PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding ) \
	X(PFNGLVERTEXARRAYVERTEXBUFFERPROC,  glVertexArrayVertexBuffer  ) \
	X(PFNGLVERTEXARRAYATTRIBFORMATPROC,  glVertexArrayAttribFormat  ) \
	X(PFNGLENABLEVERTEXARRAYATTRIBPROC,  glEnableVertexArrayAttrib  ) \
	X(PFNGLCREATESHADERPROGRAMVPROC,     glCreateShaderProgramv     ) \
	X(PFNGLGETPROGRAMIVPROC,             glGetProgramiv             ) \
	X(PFNGLGETPROGRAMINFOLOGPROC,        glGetProgramInfoLog        ) \
	X(PFNGLGENPROGRAMPIPELINESPROC,      glGenProgramPipelines      ) \
	X(PFNGLUSEPROGRAMSTAGESPROC,         glUseProgramStages         ) \
	X(PFNGLBINDPROGRAMPIPELINEPROC,      glBindProgramPipeline      ) \
	X(PFNGLPROGRAMUNIFORMMATRIX2FVPROC,  glProgramUniformMatrix2fv  ) \
	X(PFNGLDEBUGMESSAGECALLBACKPROC,     glDebugMessageCallback     )

#define X(type, name) type name;
GL_FUNCTIONS(X)
#undef X

#endif