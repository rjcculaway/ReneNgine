#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (location = 0) out vec4 fragment_color;

uniform float time;
uniform vec3 view_position;
uniform vec3 light_position;
uniform vec3 light_color;

uniform sampler2D texture_sampler1;
uniform sampler2D texture_sampler2;

uniform float specular_strength;
uniform float shininess;
uniform vec3 ambient;

float triangle_wave(float time, float period) {
	float time_per_period = time / period;
	return 2 * abs(time_per_period - floor(time_per_period + 0.5));
}

void main () {
	vec3 normal_normalized = normalize(normal);
	
	vec3 light_direction = normalize(light_position - position.xyz);
	vec3 view_direction = normalize(view_position - position.xyz);
	vec3 reflection_direction = reflect(-light_direction, normal_normalized); // The light direction is negated since reflect expects that the vector goes from the light to the fragment position, not the other way around

	float specular_factor = pow(max(dot(view_direction, reflection_direction), 0.0), shininess);
	vec3 specular = specular_strength * specular_factor * light_color;

	vec3 color = mix(texture(texture_sampler1, uv), texture(texture_sampler2, uv), triangle_wave(time, 3.0)).rgb;
	float diffuse_factor = max(dot(normal_normalized, light_direction), 0.0);
	vec3 lambertian = diffuse_factor * light_color;

	vec3 result = (ambient + lambertian + specular) * color;

	fragment_color = vec4(result, 1.0);
}