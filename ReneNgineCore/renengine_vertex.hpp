#pragma once

#include <glm/glm.hpp>

namespace ReneNgine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normals;
		glm::vec2 texture_coordinates;
	};
}