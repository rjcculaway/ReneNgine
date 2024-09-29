#version 460 core

layout (location = 0) in vec2 uv;

layout (location = 0) out vec4 color;

uniform sampler2D screen_texture;

void main () {
	color = texture(screen_texture, uv);
}