#ifndef DEBUG
#define DEBUG 1
#endif

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
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

typedef const char * (*PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
typedef BOOL (*PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int32_t* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int32_t* piFormats, UINT* nNumFormats);
typedef HGLRC (*PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int32_t* attribList);
typedef BOOL (*PFNWGLSWAPINTERVALEXTPROC)(int32_t int32_terval);

static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;


struct {
	HINSTANCE instance;
	HWND      win_handler;
	HDC       device_ctx;
	HGLRC     gl_ctx;
}
static self = { 0 };

// Display a message box with an error text
static void panic(const char* message) {
	MessageBoxA(NULL, message, "Error", MB_ICONEXCLAMATION);
	ExitProcess(0);
}

static LPWSTR utf8_to_utf16(const char* utf8) {
	int32_t len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	LPWSTR utf16 = calloc(len, sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16, len);

	return utf16;
}

#ifdef DEBUG
static void debug_callback(
	GLenum source, GLenum type, GLuint32 id, GLenum severity,
	GLsizei length, const GLchar* message, const void* user)
{
	(void)source;
	(void)type;
	(void)id;
	(void)length;
	(void)user;

	OutputDebugStringA(message);
	OutputDebugStringA("\n");
	if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) {
		if (IsDebuggerPresent()) {
			assert(!"OpenGL error - check the callstack in debugger");
		}
		panic("OpenGL API usage error! Use debugger to examine call stack!");
	}
}
#endif

static LRESULT CALLBACK win_proc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(wnd, msg, wparam, lparam);
}

static void load_wgl_funcs(void) {
	// To get WGL functions we need valid GL context,
	// so create dummy window for dummy GL contetx.
	HWND dummy = CreateWindowExW(
		0, L"STATIC", L"DummyWindow", WS_OVERLAPPED,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, NULL, NULL);
	assert(dummy && "Failed to create dummy window");

	HDC dc = GetDC(dummy);
	assert(dc && "Failed to get device context for dummy window");

	PIXELFORMATDESCRIPTOR desc = {
		.nSize = sizeof(desc),
		.nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType = PFD_TYPE_RGBA,
		.cColorBits = 24,
	};

	int32_t format = ChoosePixelFormat(dc, &desc);
	if (!format) {
		panic("Cannot choose OpenGL pixel format for dummy window!");
	}

	int32_t ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
	assert(ok && "Failed to describe OpenGL pixel format");

	// Reason to create dummy window is that SetPixelFormat can be called only once for the window
	if (!SetPixelFormat(dc, format, &desc)) {
		panic("Cannot set OpenGL pixel format for dummy window!");
	}

	HGLRC rc = wglCreateContext(dc);
	assert(rc && "Failed to create OpenGL context for dummy window");

	ok = wglMakeCurrent(dc, rc);
	assert(ok && "Failed to make current OpenGL context for dummy window");

	// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
	wglChoosePixelFormatARB = (void*)wglGetProcAddress("wglChoosePixelFormatARB");
	// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
	wglCreateContextAttribsARB = (void*)wglGetProcAddress("wglCreateContextAttribsARB");
	// https://www.khronos.org/registry/OpenGL/extensions/EXT/WGL_EXT_swap_control.txt
	wglSwapIntervalEXT = (void*)wglGetProcAddress("wglSwapIntervalEXT");

	if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB || !wglSwapIntervalEXT) {
		panic("OpenGL does not support required WGL extensions for modern context!");
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(rc);
	ReleaseDC(dummy, dc);
	DestroyWindow(dummy);
}

void os_create_window(int32_t width, int32_t height, const char *name) {
	assert(self.win_handler == NULL && "Window already created");

	// register window class to have custom WindowProc callback
	WNDCLASSEXW wc =
	{
		.cbSize = sizeof(wc),
		.lpfnWndProc = win_proc,
		.hInstance = self.instance,
		.hIcon = LoadIcon(NULL, IDI_APPLICATION),
		.hCursor = LoadCursor(NULL, IDC_ARROW),
		.lpszClassName = L"opengl_window_class",
	};
	ATOM atom = RegisterClassExW(&wc);
	assert(atom && "Failed to register window class");

	// window properties - width, height and style
	DWORD exstyle = WS_EX_APPWINDOW;
	DWORD style = WS_OVERLAPPEDWINDOW;

	// create window
	self.win_handler = CreateWindowExW(
		exstyle, wc.lpszClassName, utf8_to_utf16(name), style,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, wc.hInstance, NULL);
	assert(self.win_handler && "Failed to create window");

	// Lets create an OpenGL context
	self.device_ctx = GetDC(self.win_handler);
	assert(self.device_ctx && "Failed to window device context");

	// Pixel format
	{
		int32_t attrib[] = {
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

		int32_t format;
		UINT formats;
		if (!wglChoosePixelFormatARB(self.device_ctx, attrib, NULL, 1, &format, &formats) || formats == 0) {
			panic("OpenGL does not support required pixel format!");
		}

		PIXELFORMATDESCRIPTOR desc = { .nSize = sizeof(desc) };
		int32_t ok = DescribePixelFormat(self.device_ctx, format, sizeof(desc), &desc);
		assert(ok && "Failed to describe OpenGL pixel format");

		if (!SetPixelFormat(self.device_ctx, format, &desc)) {
			panic("Cannot set OpenGL selected pixel format!");
		}
	}

	// Modern context
	{
		int attrib[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, GL_MAJOR,
			WGL_CONTEXT_MINOR_VERSION_ARB, GL_MINOR,
			WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef DEBUG
			// Ask for debug context for non "Release" builds
			// this is so we can enable debug callback
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0,
		};

		HGLRC rc = wglCreateContextAttribsARB(self.device_ctx, NULL, attrib);
		if (!rc) {
			panic("Cannot create modern OpenGL context! OpenGL version 4.5 not supported?");
		}
		self.gl_ctx = rc;

		BOOL ok = wglMakeCurrent(self.device_ctx, rc);
		assert(ok && "Failed to make current OpenGL context");

		// Load OpenGL functions
#define X(type, name) name = (type)wglGetProcAddress(#name); assert(name);
		GL_FUNCTIONS(X)
#undef X

#ifdef DEBUG
		// Enable debug callback
		glDebugMessageCallback(&debug_callback, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
	}

	// Show the window
	wglSwapIntervalEXT(true);
	ShowWindow(self.win_handler, SW_SHOWDEFAULT);
}

bool os_window_should_close() {
	MSG msg;
	if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return true;
		}
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return false;
}

bool os_window_is_visible() {
	RECT rect;
	GetClientRect(self.win_handler, &rect);
	int32_t width = rect.right - rect.left;
	int32_t height = rect.bottom - rect.top;

	return width != 0 && height != 0;
}

void os_swap_buffers() {
	if (!SwapBuffers(self.device_ctx)) {
		panic("Failed to swap OpenGL buffers!");
	}
}

void os_sleep(uint32_t miliseconds) {
	Sleep(miliseconds);
}

// Entry point defined by the user
int32_t entry_point ( void );

int32_t WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR cmd, int32_t show) {
	(void)prev;
	(void)cmd;
	(void)show;

	self.instance = instance;
	load_wgl_funcs();
	return entry_point();
}