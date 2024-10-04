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
				movement = movement | CameraDirection::LEFT;
				break;
			case SDLK_d:
				movement = movement | CameraDirection::RIGHT;
				break;
			case SDLK_w:
				movement = movement | CameraDirection::FRONT;
				break;
			case SDLK_s:
				movement = movement | CameraDirection::BACK;
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_a:
				movement = movement & ~CameraDirection::LEFT;
				break;
			case SDLK_d:
				movement = movement & ~CameraDirection::RIGHT;
				break;
			case SDLK_w:
				movement = movement & ~CameraDirection::FRONT;
				break;
			case SDLK_s:
				movement = movement & ~CameraDirection::BACK;
			}
		}
	}

	void Camera::Process(const double delta_time = 0.0) {
		double camera_speed_in_time = camera_speed * delta_time;
		if (movement & CameraDirection::FRONT) {
			transform.position += static_cast<float>(camera_speed_in_time) * FRONT_VECTOR;
		}
		else if (movement & CameraDirection::BACK) {
			transform.position -= static_cast<float>(camera_speed_in_time) * FRONT_VECTOR;
		}
		if (movement & CameraDirection::LEFT) {
			transform.position -= glm::normalize(glm::cross(UP_VECTOR, FRONT_VECTOR)) * static_cast<float>(camera_speed_in_time);
		}
		else if (movement & CameraDirection::RIGHT) {
			transform.position += glm::normalize(glm::cross(UP_VECTOR, FRONT_VECTOR)) * static_cast<float>(camera_speed_in_time);
		}
		//transform.position = glm::vec3(cos(delta_time) * 15.0, sin(delta_time) * 15.0, 0.0);
	}

	glm::mat4 Camera::GetViewMatrix() {
		// TODO: Cache view matrix if no changes to the transform
		/*
		* Manual computation of the look at vector
		*/
		//glm::vec3 camera_target(0.0, 0.0, 15.0);
		/*
		glm::vec3 camera_direction = transform.position - camera_target;

		glm::vec3 camera_right = glm::normalize(glm::cross(up_vector, camera_direction));
		glm::vec3 camera_up = glm::cross(camera_direction, camera_right);
		*/
		view_matrix = glm::lookAt(transform.position, transform.position + FRONT_VECTOR, UP_VECTOR);
		return view_matrix;
	}
}