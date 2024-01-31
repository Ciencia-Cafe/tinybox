#version 330 core

out vec4 colour;

in vec4 color;
in vec2 uv;

void main() {
	colour = vec4(color);
}