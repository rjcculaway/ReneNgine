#pragma once

#include <SDL.h>

namespace ReneNgine {
	class Renderer {
	public:
		virtual void Render() = 0;
		virtual void HandleRendererEvents(const SDL_Event& event) = 0;
	};
}