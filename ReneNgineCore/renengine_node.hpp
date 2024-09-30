#pragma once

#include "renengine_transform.hpp"

#include <vector>
#include <memory>

#include <SDL.h>

namespace ReneNgine {
	class Node
	{
	public:
		Transform transform;

		void HandleInput(const SDL_Event event);
		void HandleProcess(const uint64_t delta_time);

		virtual void Input(const SDL_Event event) { return; }
		virtual void Process(const uint64_t delta_time) { return; }
	private:
		std::vector<std::unique_ptr<Node>> children;
		bool is_dirty = true;
	};
}

