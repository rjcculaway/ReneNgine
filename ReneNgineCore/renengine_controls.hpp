#pragma once

#include <SDL.h>

namespace ReneNgine {
	class Controls {
	public:
		bool HandleEvents();
	private:
		SDL_Event event;
	};
}
