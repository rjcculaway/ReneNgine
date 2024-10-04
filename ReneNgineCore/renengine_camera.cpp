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
		else if (event.type == SDL_MOUSEMOTION) {
			int x = 0, y = 0;
			SDL_GetRelativeMouseState(&x, &y);

			float pitch = transform.rotation.x - glm::radians(static_cast<float>(y) * camera_sensitivity);
			if (pitch >= glm::half_pi<float>()) {
				pitch = glm::half_pi<float>() - 0.1;
			}
			else if (pitch <= -glm::half_pi<float>()) {
				pitch = -glm::half_pi<float>() + 0.1;
			}
			
			float yaw = transform.rotation.y - glm::radians(static_cast<float>(x) * camera_sensitivity);
			
			transform.rotation = glm::vec3(
					pitch,	// Pitch
					yaw,	// Yaw
					transform.rotation.z);
		}
	}

	void Camera::Process(const double delta_time = 0.0) {
		double camera_speed_in_time = camera_speed * delta_time;

		float sin_yaw = sinf(transform.rotation.y);
		float sin_pitch = sinf(transform.rotation.x);
		float cos_yaw = cosf(transform.rotation.y);
		float cos_pitch = cosf(transform.rotation.x);

		glm::vec3 new_direction = glm::vec3(
			cos_yaw * cos_pitch,
			sin_pitch,
			sin_yaw * cos_pitch);
		front = glm::normalize(new_direction);

		if (movement & CameraDirection::FRONT) {
			transform.position += front * static_cast<float>(camera_speed_in_time);
		}
		else if (movement & CameraDirection::BACK) {
			transform.position -= front * static_cast<float>(camera_speed_in_time);
		}
		if (movement & CameraDirection::LEFT) {
			transform.position -= glm::normalize(glm::cross(UP_VECTOR, front)) * static_cast<float>(camera_speed_in_time);
		}
		else if (movement & CameraDirection::RIGHT) {
			transform.position += glm::normalize(glm::cross(UP_VECTOR, front)) * static_cast<float>(camera_speed_in_time);
		}
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
		//SDL_Log("front: %f, %f, %f", front.x, front.y, front.z);
		view_matrix = glm::lookAt(transform.position, transform.position + front, UP_VECTOR);
		return view_matrix;
	}
}