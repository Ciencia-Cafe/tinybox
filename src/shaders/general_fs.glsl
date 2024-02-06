#version 330 core

out vec4 colour;

in vec4 color;
in vec2 uv;

uniform sampler2D tex;

void main() {
	// SDF font rendering
	float alpha = texture(tex, uv).r;
	vec2 tex_size = vec2(textureSize(tex, 0));
	vec2 density = fwidth(uv) * tex_size;
	float m = min(density.x, density.y);
	float inv = 1.0 / m;
	float a = (alpha - 128.0/255.0 + 24.0/255.0*m*0.5) * 255.0/24.0 * inv;
	colour = vec4(1.0, 1.0, 1.0, a);
}