#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (location = 0) out vec4 fragment_color;

uniform vec3 light_position;
uniform sampler2D texture_sampler1;
uniform sampler2D texture_sampler2;

const vec3 ambient = vec3(0.0, 0.08, 0.112);

void main () {
	vec3 normal_normalized = normalize(normal);
	vec3 light_direction = normalize(light_position - position.xyz);
	vec3 color = mix(texture(texture_sampler1, uv), texture(texture_sampler2, uv), 0.5).rgb;
	float lambertian = max(dot(normal_normalized, light_direction), 0.0);

	vec3 result = (ambient + lambertian) * color;

	fragment_color = vec4(result, 1.0);
}