#include "renengine_transform.hpp"

#define GLM_FORCE_LEFT_HANDED
#include <glm/ext/matrix_transform.hpp>

namespace ReneNgine {
	glm::mat4 Transform::GetModelMatrix() {
		// TODO: Implement cached model matrix if unchanged
		model_matrix = glm::identity<glm::mat4>();
		model_matrix = glm::scale(model_matrix, scale);
		model_matrix = glm::rotate(model_matrix, rotation.x, glm::vec3(1.0, 0.0, 0.0));
		model_matrix = glm::rotate(model_matrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
		model_matrix = glm::rotate(model_matrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));
		model_matrix = glm::translate(model_matrix, position);

		return model_matrix;
	}
}