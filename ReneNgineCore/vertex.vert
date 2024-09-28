#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 0) out vec4 fragment_position;
layout (location = 1) out vec3 fragment_normal;
layout (location = 2) out vec2 fragment_uv;

uniform mat4 transform;

void main () {
	vec4 transformed_position = transform * vec4(position, 1.0);	// Column major, post multiplication 
	gl_Position = transformed_position;
	fragment_position = vec4(position, 1.0);
}
