#include <windows.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "os_opengl.h"
#include "os_api.h"

#if defined(_WIN32) || defined(_WIN64)
#include "os_win32.c"
#endif

int entry_point ( void ) {
	os_create_window(800, 600, "hello sailor");

	// TODO(ellora): Move to logging system
	printf("[LOG] %s\n", glGetString(GL_VERSION));

	while (!os_window_should_close()) {
		if (os_window_is_visible()) {
			glClearColor(0.1f, 0.2f, 0.3f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			os_swap_buffers();
		}
		else {
			os_sleep(17);
		}
	}

	return 0;
}