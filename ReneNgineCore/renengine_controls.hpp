#pragma once

#include <SDL.h>

namespace ReneNgine {
	class Controls {
	public:
		bool HandleControlEvents(const SDL_Event& event);
	};
}
