#include <windows.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "lin_math.c"
#include "arena.c"

#include "os_api.h"
#include "os_opengl.h"
#include "gfx_api.h"

#if defined(_WIN32) || defined(_WIN64)
#include "gfx_opengl.c"
#include "os_win32.c"
#endif

int entry_point ( void ) {
	os_create_window(800, 600, "hello sailor");

	// Lets test arena
{
	Arena arena;
#define PRINT(call) call;printf("Arena: size=%zu offset=%zu\n", arena.size, arena.offset)
	PRINT(arena_init(&arena, 4096));
	const char *str = arena_sprintf(&arena, "Hello %s", "World");
	PRINT(printf("alocates: %s\n", str));
	PRINT(arena_reset(&arena));
	arena_destroy(&arena);
#undef PRINT
}

	gfx_init();

	while (!os_window_should_close()) {
		if (os_window_is_visible()) {
			gfx_begin();
			gfx_end();
			os_swap_buffers();
		}
		else {
			os_sleep(17);
		}
	}

	return 0;
}