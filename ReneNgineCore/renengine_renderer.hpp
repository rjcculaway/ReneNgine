#pragma once

#include <SDL.h>

namespace ReneNgine {
	class Renderer {
	public:
		virtual void Render(uint64_t delta_time_ms) = 0;
		virtual void HandleRendererEvents(const SDL_Event& event) = 0;
	};
}