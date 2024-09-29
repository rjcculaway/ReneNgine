#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (location = 0) out vec4 fragment_position;
layout (location = 1) out vec3 fragment_normal;
layout (location = 2) out vec2 fragment_uv;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;

void main () {
	vec4 world_space_position = model_matrix * vec4(position, 1.0);	// Column major, post multiplication 
	fragment_position = world_space_position;
	fragment_normal = normal_matrix * normal;
	fragment_uv = uv;
	gl_Position = projection_matrix * world_space_position;
}
