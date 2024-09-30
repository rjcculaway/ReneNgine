#pragma once

#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>

namespace ReneNgine {
	class Transform
	{
	public:
		glm::vec3 position{ 0.0, 0.0, 0.0 };
		glm::vec3 rotation{ 0.0, 0.0, 0.0 };
		glm::vec3 scale{ 1.0, 1.0, 1.0 };

		glm::mat4 GetModelMatrix();
	private:
		glm::mat4 model_matrix = GetModelMatrix();
		// bool is_dirty;
	};
}

