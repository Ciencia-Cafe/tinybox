#ifndef GFX_API_H
#define GFX_API_H

#include <inttypes.h>

typedef struct { float r, g, n, a; } gfx_Color;

typedef struct
{
	float x, y;        // Position
	float r, g, b, a;  // Color
	float u, v;        // Texture coords
}
gfx_Vertex;

typedef struct
{
	uint32_t id;
	int32_t width;
	int32_t height;
}
gfx_Image;

// TODO(ellora):
// typedef struct {}  gfx_Font;

// Should be defined from the API implementation
void gfx_init();
void gfx_begin();
void gfx_end();
void gfx_set_color(gfx_Color c);
void gfx_set_image(gfx_Image *i);
void gfx_send_rec_ex(float x, float y, float w, float h, float u0, float u1, float v0, float v1);

#endif