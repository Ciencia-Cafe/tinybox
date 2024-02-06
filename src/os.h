// Copyright 2023 Elloramir.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#ifndef TINYBOX_OS_H
#define TINYBOX_OS_H

#include "math.h"
#include <stdbool.h>
#include <inttypes.h>

void  os_create_window(int32_t width, int32_t height, const char *name);
void  os_sleep(uint32_t miliseconds);
bool  os_window_should_close();
vec2  os_window_size();
bool  os_window_is_visible();
void  os_swap_buffers();
void  os_panic(const char *msg);
void *os_load_file(const char *filename);

#endif