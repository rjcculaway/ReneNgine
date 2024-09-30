#pragma once

#include <memory>

#include <SDL.h>

namespace ReneNgine {
	class Camera;
	class Node;
	class Scene {
	public:
		Scene();
		void HandleInput(const SDL_Event event);
		void HandleProcess(const uint64_t delta_time);
		Camera * GetActiveCamera() const;
		void SetActiveCamera(Camera* camera) { active_camera = camera; }
	private:
		std::unique_ptr<Node> scene_tree = std::make_unique<Node>(this);

		Camera * active_camera = nullptr;
	};
}

