#include <windows.h>
#include <inttypes.h>

#define DEBUG_MODE 1
#define GL_MAJOR 3
#define GL_MINOR 3

// Only used on this file
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef char GLchar;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLuint;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
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


typedef void (APIENTRY* PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (APIENTRY* PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags);
typedef void (APIENTRY* PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (APIENTRY* PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void (APIENTRY* PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRY* PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRY* PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRY* PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
typedef GLuint(APIENTRY* PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar* const* strings);
typedef void (APIENTRY* PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
typedef void (APIENTRY* PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void (APIENTRY* PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint* pipelines);
typedef void (APIENTRY* PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (APIENTRY* PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (APIENTRY* PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY* PFNGLBINDTEXTUREUNITPROC)(GLuint unit, GLuint texture);
typedef void (APIENTRY* PFNGLCREATETEXTURESPROC)(GLenum target, GLsizei n, GLuint* textures);
typedef void (APIENTRY* PFNGLTEXTUREPARAMETERIPROC)(GLuint texture, GLenum pname, GLint param);
typedef void (APIENTRY* PFNGLTEXTURESTORAGE2DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRY* PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
typedef void (APIENTRY* PFNGLDEBUGMESSAGECALLBACKPROC)(void* callback, const void* userParam);
typedef void (APIENTRY* PFNGLENABLEPROC)(GLenum cap);
typedef void (APIENTRY* PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (APIENTRY* PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY* PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRY* PFNGLCLEARPROC)(GLbitfield mask);
typedef void (APIENTRY* PFNGLDISABLEPROC)(GLenum cap);
typedef void (APIENTRY* PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);

// OpenGL 1.0 functions
PFNGLENABLEPROC glEnable(GLenum cap);
PFNGLBLENDFUNCPROC glBlendFunc(GLenum sfactor, GLenum dfactor);
PFNGLVIEWPORTPROC glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCLEARCOLORPROC glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCLEARPROC glClear(GLbitfield mask);
PFNGLDISABLEPROC glDisable(GLenum cap);
PFNGLDRAWARRAYSPROC glDrawArrays(GLenum mode, GLint first, GLsizei count);

#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_TYPE_RGBA_ARB 0x202B
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001

typedef const char* (APIENTRY* PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
typedef BOOL(APIENTRY* PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
typedef HGLRC(APIENTRY* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int* attribList);
typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALEXTPROC)(int interval);

static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

#define _USE_MATH_DEFINES
#include <math.h>
#include <stddef.h>

// replace this with your favorite Assert() implementation
#include <intrin.h>
#define Assert(cond) do { if (!(cond)) __debugbreak(); } while (0)

// This macro can dine and load those GL functions
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
	X(PFNGLBINDTEXTUREUNITPROC,          glBindTextureUnit          ) \
	X(PFNGLCREATETEXTURESPROC,           glCreateTextures           ) \
	X(PFNGLTEXTUREPARAMETERIPROC,        glTextureParameteri        ) \
	X(PFNGLTEXTURESTORAGE2DPROC,         glTextureStorage2D         ) \
	X(PFNGLTEXTURESUBIMAGE2DPROC,        glTextureSubImage2D        ) \
	X(PFNGLDEBUGMESSAGECALLBACKPROC,     glDebugMessageCallback     )

#define X(type, name) static type name;
GL_FUNCTIONS(X)
#undef X

#define STR2(x) #x
#define STR(x) STR2(x)

static void FatalError(const char* message)
{
	MessageBoxA(NULL, message, "Error", MB_ICONEXCLAMATION);
	ExitProcess(0);
}

#ifndef DEBUG_MODE
static void APIENTRY debug_callback(
	GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* user)
{
	OutputDebugStringA(message);
	OutputDebugStringA("\n");
	if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM)
	{
		if (IsDebuggerPresent())
		{
			Assert(!"OpenGL error - check the callstack in debugger");
		}
		FatalError("OpenGL API usage error! Use debugger to examine call stack!");
	}
}
#endif

static LRESULT CALLBACK WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcW(wnd, msg, wparam, lparam);
}

// compares src string with dstlen characters from dst, returns 1 if they are equal, 0 if not
static int StringsAreEqual(const char* src, const char* dst, size_t dstlen)
{
	while (*src && dstlen-- && *dst)
	{
		if (*src++ != *dst++)
		{
			return 0;
		}
	}

	return (dstlen && *src == *dst) || (!dstlen && *src == 0);
}

static void GetWglFunctions(void)
{
	// to get WGL functions we need valid GL context, so create dummy window for dummy GL contetx
	HWND dummy = CreateWindowExW(
		0, L"STATIC", L"DummyWindow", WS_OVERLAPPED,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, NULL, NULL);
	Assert(dummy && "Failed to create dummy window");

	HDC dc = GetDC(dummy);
	Assert(dc && "Failed to get device context for dummy window");

	PIXELFORMATDESCRIPTOR desc =
	{
		.nSize = sizeof(desc),
		.nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType = PFD_TYPE_RGBA,
		.cColorBits = 24,
	};

	int format = ChoosePixelFormat(dc, &desc);
	if (!format)
	{
		FatalError("Cannot choose OpenGL pixel format for dummy window!");
	}

	int ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
	Assert(ok && "Failed to describe OpenGL pixel format");

	// reason to create dummy window is that SetPixelFormat can be called only once for the window
	if (!SetPixelFormat(dc, format, &desc))
	{
		FatalError("Cannot set OpenGL pixel format for dummy window!");
	}

	HGLRC rc = wglCreateContext(dc);
	Assert(rc && "Failed to create OpenGL context for dummy window");

	ok = wglMakeCurrent(dc, rc);
	Assert(ok && "Failed to make current OpenGL context for dummy window");

	// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_extensions_string.txt
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB =
		(void*)wglGetProcAddress("wglGetExtensionsStringARB");
	if (!wglGetExtensionsStringARB)
	{
		FatalError("OpenGL does not support WGL_ARB_extensions_string extension!");
	}

	const char* ext = wglGetExtensionsStringARB(dc);
	Assert(ext && "Failed to get OpenGL WGL extension string");

	const char* start = ext;
	for (;;)
	{
		while (*ext != 0 && *ext != ' ')
		{
			ext++;
		}

		size_t length = ext - start;
		if (StringsAreEqual("WGL_ARB_pixel_format", start, length))
		{
			// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
			wglChoosePixelFormatARB = (void*)wglGetProcAddress("wglChoosePixelFormatARB");
		}
		else if (StringsAreEqual("WGL_ARB_create_context", start, length))
		{
			// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
			wglCreateContextAttribsARB = (void*)wglGetProcAddress("wglCreateContextAttribsARB");
		}
		else if (StringsAreEqual("WGL_EXT_swap_control", start, length))
		{
			// https://www.khronos.org/registry/OpenGL/extensions/EXT/WGL_EXT_swap_control.txt
			wglSwapIntervalEXT = (void*)wglGetProcAddress("wglSwapIntervalEXT");
		}

		if (*ext == 0)
		{
			break;
		}

		ext++;
		start = ext;
	}

	if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB || !wglSwapIntervalEXT)
	{
		FatalError("OpenGL does not support required WGL extensions for modern context!");
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(rc);
	ReleaseDC(dummy, dc);
	DestroyWindow(dummy);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previnstance, LPSTR cmdline, int cmdshow)
{
	// get WGL functions to be able to create modern GL context
	GetWglFunctions();

	// register window class to have custom WindowProc callback
	WNDCLASSEXW wc =
	{
		.cbSize = sizeof(wc),
		.lpfnWndProc = WindowProc,
		.hInstance = instance,
		.hIcon = LoadIcon(NULL, IDI_APPLICATION),
		.hCursor = LoadCursor(NULL, IDC_ARROW),
		.lpszClassName = L"opengl_window_class",
	};
	ATOM atom = RegisterClassExW(&wc);
	Assert(atom && "Failed to register window class");

	// window properties - width, height and style
	int width = CW_USEDEFAULT;
	int height = CW_USEDEFAULT;
	DWORD exstyle = WS_EX_APPWINDOW;
	DWORD style = WS_OVERLAPPEDWINDOW;

	// uncomment in case you want fixed size window
	// style &= ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
	// RECT rect = { 0, 0, 1280, 720 };
	// AdjustWindowRectEx(&rect, style, FALSE, exstyle);
	// width = rect.right - rect.left;
	// height = rect.bottom - rect.top;

	// create window
	HWND window = CreateWindowExW(
		exstyle, wc.lpszClassName, L"OpenGL Window", style,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, wc.hInstance, NULL);
	Assert(window && "Failed to create window");

	HDC dc = GetDC(window);
	Assert(dc && "Failed to window device context");

	// set pixel format for OpenGL context
	{
		int attrib[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
			WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB,     24,
			WGL_DEPTH_BITS_ARB,     24,
			WGL_STENCIL_BITS_ARB,   8,

			// uncomment for sRGB framebuffer, from WGL_ARB_framebuffer_sRGB extension
			// https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_framebuffer_sRGB.txt
			//WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,

			// uncomment for multisampeld framebuffer, from WGL_ARB_multisample extension
			// https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_multisample.txt
			//WGL_SAMPLE_BUFFERS_ARB, 1,
			//WGL_SAMPLES_ARB,        4, // 4x MSAA
			0,
		};

		int format;
		UINT formats;
		if (!wglChoosePixelFormatARB(dc, attrib, NULL, 1, &format, &formats) || formats == 0)
		{
			FatalError("OpenGL does not support required pixel format!");
		}

		PIXELFORMATDESCRIPTOR desc = { .nSize = sizeof(desc) };
		int ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
		Assert(ok && "Failed to describe OpenGL pixel format");

		if (!SetPixelFormat(dc, format, &desc))
		{
			FatalError("Cannot set OpenGL selected pixel format!");
		}
	}

	// create modern OpenGL context
	{
		int attrib[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, GL_MAJOR,
			WGL_CONTEXT_MINOR_VERSION_ARB, GL_MINOR,
			WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifndef DEBUG_MODE
			// ask for debug context for non "Release" builds
			// this is so we can enable debug callback
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0,
		};

		HGLRC rc = wglCreateContextAttribsARB(dc, NULL, attrib);
		if (!rc)
		{
			FatalError("Cannot create modern OpenGL context! OpenGL version 4.5 not supported?");
		}

		BOOL ok = wglMakeCurrent(dc, rc);
		Assert(ok && "Failed to make current OpenGL context");

		// load OpenGL functions
#define X(type, name) name = (type)wglGetProcAddress(#name); Assert(name);
		GL_FUNCTIONS(X)
#undef X

#ifndef DEBUG_MODE
		// enable debug callback
		glDebugMessageCallback(&debug_callback, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
	}

	// set to FALSE to disable vsync
	BOOL vsync = TRUE;
	wglSwapIntervalEXT(vsync ? 1 : 0);

	// show the window
	ShowWindow(window, SW_SHOWDEFAULT);

	LARGE_INTEGER freq, c1;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&c1);

	for (;;)
	{
		// process all incoming Windows messages
		MSG msg;
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
			continue;
		}

		// get current window client area size
		RECT rect;
		GetClientRect(window, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;

		// render only if window size is non-zero
		if (width != 0 && height != 0)
		{
			// setup output size covering all client area of window
			glViewport(0, 0, width, height);

			// clear screen
			glClearColor(0.392f, 0.584f, 0.929f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			// swap the buffers to show output
			if (!SwapBuffers(dc))
			{
				FatalError("Failed to swap OpenGL buffers!");
			}
		}
		else
		{
			// window is minimized, cannot vsync - instead sleep a bit
			if (vsync)
			{
				Sleep(10);
			}
		}
	}
}
