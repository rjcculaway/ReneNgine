#include "renengine_camera.hpp"
#include "renengine_scene.hpp"

#include <iostream>

#define GLM_FORCE_LEFT_HANDED
#include <glm/ext/matrix_transform.hpp>

namespace ReneNgine {
	void Camera::MakeActiveCamera() { 
		scene->SetActiveCamera(this); 
	}
	void Camera::Input(const SDL_Event event) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_a:
				transform.position += glm::vec3(-0.1, 0.0, 0.0);
				break;
			case SDLK_d:
				transform.position += glm::vec3(0.1, 0.0, 0.0);
				break;
			case SDLK_w:
				transform.position += glm::vec3(0.0, 0.0, 0.1);
				break;
			case SDLK_s:
				transform.position += glm::vec3(0.0, 0.0, -0.1);
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {

		}
	}

	void Camera::Process(uint64_t delta_time) {
		float seconds = static_cast<float>(delta_time) / 1000.0;
		//transform.position = glm::vec3(cos(seconds) * 15.0, sin(seconds) * 15.0, 0.0);
	}

	glm::mat4 Camera::GetViewMatrix() {
		// TODO: Cache view matrix if no changes to the transform
		/*
		* Manual computation of the look at vector
		*/
		glm::vec3 camera_target(0.0, 0.0, 15.0);
		/*
		glm::vec3 camera_direction = transform.position - camera_target;

		glm::vec3 camera_right = glm::normalize(glm::cross(up_vector, camera_direction));
		glm::vec3 camera_up = glm::cross(camera_direction, camera_right);
		*/
		view_matrix = glm::lookAt(transform.position, camera_target, up_vector);
		return view_matrix;
	}
}