#pragma once

#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>

namespace ReneNgine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_coordinates;
	};
}