#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (location = 0) out vec4 fragment_color;

uniform sampler2D texture_sampler;

void main () {
	fragment_color = texture(texture_sampler, uv);
	//fragment_color = vec4(uv, 1.0, 1.0);
}