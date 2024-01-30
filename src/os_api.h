#ifndef OS_API_H
#define OS_API_H

#include <inttypes.h>

void os_create_window(int32_t width, int32_t height, const char *name);
void os_sleep(uint32_t miliseconds);
bool os_window_should_close();
vec2 os_window_size();
bool os_window_is_visible();
void os_swap_buffers();

#endif