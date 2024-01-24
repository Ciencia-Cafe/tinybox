#include "opengl.h"

#include <windows.h>
#include <assert.h>
#include <string.h>

#define DEBUG_MODE 1
#define GL_MAJOR 3
#define GL_MINOR 3

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

static void panic(const char* message)
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
			assert(!"OpenGL error - check the callstack in debugger");
		}
		panic("OpenGL API usage error! Use debugger to examine call stack!");
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

static void GetWglFunctions(void)
{
	// to get WGL functions we need valid GL context, so create dummy window for dummy GL contetx
	HWND dummy = CreateWindowExW(
		0, L"STATIC", L"DummyWindow", WS_OVERLAPPED,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, NULL, NULL);
	assert(dummy && "Failed to create dummy window");

	HDC dc = GetDC(dummy);
	assert(dc && "Failed to get device context for dummy window");

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
		panic("Cannot choose OpenGL pixel format for dummy window!");
	}

	int ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
	assert(ok && "Failed to describe OpenGL pixel format");

	// reason to create dummy window is that SetPixelFormat can be called only once for the window
	if (!SetPixelFormat(dc, format, &desc))
	{
		panic("Cannot set OpenGL pixel format for dummy window!");
	}

	HGLRC rc = wglCreateContext(dc);
	assert(rc && "Failed to create OpenGL context for dummy window");

	ok = wglMakeCurrent(dc, rc);
	assert(ok && "Failed to make current OpenGL context for dummy window");

	// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_extensions_string.txt
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB =
		(void*)wglGetProcAddress("wglGetExtensionsStringARB");
	if (!wglGetExtensionsStringARB)
	{
		panic("OpenGL does not support WGL_ARB_extensions_string extension!");
	}

	const char* ext = wglGetExtensionsStringARB(dc);
	assert(ext && "Failed to get OpenGL WGL extension string");

	const char* start = ext;
	for (;;)
	{
		while (*ext != 0 && *ext != ' ')
		{
			ext++;
		}

		size_t length = ext - start;
		if (strncmp("WGL_ARB_pixel_format", start, length) == 0)
		{
			// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
			wglChoosePixelFormatARB = (void*)wglGetProcAddress("wglChoosePixelFormatARB");
		}
		else if (strncmp("WGL_ARB_create_context", start, length) == 0)
		{
			// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
			wglCreateContextAttribsARB = (void*)wglGetProcAddress("wglCreateContextAttribsARB");
		}
		else if (strncmp("WGL_EXT_swap_control", start, length) == 0)
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
		panic("OpenGL does not support required WGL extensions for modern context!");
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
	assert(atom && "Failed to register window class");

	// window properties - width, height and style
	int width = CW_USEDEFAULT;
	int height = CW_USEDEFAULT;
	DWORD exstyle = WS_EX_APPWINDOW;
	DWORD style = WS_OVERLAPPEDWINDOW;

	// create window
	HWND window = CreateWindowExW(
		exstyle, wc.lpszClassName, L"OpenGL Window", style,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, wc.hInstance, NULL);
	assert(window && "Failed to create window");

	HDC dc = GetDC(window);
	assert(dc && "Failed to window device context");

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
			panic("OpenGL does not support required pixel format!");
		}

		PIXELFORMATDESCRIPTOR desc = { .nSize = sizeof(desc) };
		int ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
		assert(ok && "Failed to describe OpenGL pixel format");

		if (!SetPixelFormat(dc, format, &desc))
		{
			panic("Cannot set OpenGL selected pixel format!");
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
			panic("Cannot create modern OpenGL context! OpenGL version 4.5 not supported?");
		}

		BOOL ok = wglMakeCurrent(dc, rc);
		assert(ok && "Failed to make current OpenGL context");

		// load OpenGL functions
#define X(type, name) name = (type)wglGetProcAddress(#name); assert(name);
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
				panic("Failed to swap OpenGL buffers!");
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
