// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "os.h"

int entry_point ( void ) {
	os_create_window(800, 600, "hello sailor");
	while (!os_window_should_close()) {
		if (os_window_is_visible()) {
			os_swap_buffers();
		}
		else {
			os_sleep(17);
		}
	}
	return 0;
}