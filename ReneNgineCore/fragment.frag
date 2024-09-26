#version 460 core

layout (location = 0) in vec4 position;
layout (location = 0) out vec4 fragment_color;

void main () {
	fragment_color = position;
}