#pragma once

#include "renengine_scene.hpp"

#include <SDL.h>

namespace ReneNgine {
	class Renderer {
	public:
		virtual void Render(const Scene& scene, double delta_time) = 0;
		virtual void HandleRendererEvents(const SDL_Event& event) = 0;
	};
}