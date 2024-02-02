#version 330 core

out vec4 colour;

in vec4 color;
in vec2 uv;

uniform sampler2D tex;

void main() {
	colour = texture(tex, uv) * color;
}