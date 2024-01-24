#define ARENA_ALIGNMENT (sizeof(void**))

typedef struct
{
    size_t size;
    size_t offset;
    uint8_t *data;
} Arena;

void arena_init(Arena *arena, size_t size) {
    assert(size && (size & 4095) == 0);

    uint8_t *ptr = (uint8_t *)calloc(1, size);
    assert(ptr != NULL);

    arena->size = size;
    arena->offset = 0;
    arena->data = ptr;
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
}

void arena_destroy(Arena *arena) {
    free(arena->data);
}

static bool is_power_of_two(size_t x) {
    return (x & (x - 1)) == 0;
}

static uintptr_t align_forward(uintptr_t ptr, size_t alignment) {
    assert(is_power_of_two(alignment));

    uintptr_t modulo = ptr & (alignment - 1);
    if (modulo != 0) {
        ptr += alignment - modulo;
    }

    return ptr;
}

void *arena_alloc(Arena *arena, size_t size) {
    uintptr_t curr = (uintptr_t)arena->data + arena->offset;
    uintptr_t offset = align_forward(curr, ARENA_ALIGNMENT);
    offset -= (uintptr_t)arena->data;

    if (offset + size > arena->size) {
        size_t new_size = arena->size;
        while (offset + size > new_size) {
            new_size *= 2;
        }

        uint8_t *ptr = (uint8_t *)realloc(arena->data, new_size);
        assert(ptr != NULL);
        arena->data = ptr;
        arena->size = new_size;
    }

    arena->offset = offset + size;
    void *ptr = arena->data + offset;
    memset(ptr, 0, size);
    return ptr;
}

const char *arena_sprintf(Arena *arena, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	char *ptr = arena_alloc(arena, len + 1);
	va_start(args, fmt);
	vsnprintf(ptr, len + 1, fmt, args);
	va_end(args);

	return ptr;
}