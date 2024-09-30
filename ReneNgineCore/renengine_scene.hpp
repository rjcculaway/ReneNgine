#pragma once

#include "renengine_node.hpp"

#include <memory>

#include <SDL.h>

namespace ReneNgine {
	class Scene {
	public:
		void HandleInput(const SDL_Event event) { scene_tree->HandleInput(event); }
		void HandleProcess(const uint64_t delta_time) { scene_tree->HandleProcess(delta_time); }
	private:
		std::unique_ptr<Node> scene_tree = std::make_unique<Node>();
	};
}

