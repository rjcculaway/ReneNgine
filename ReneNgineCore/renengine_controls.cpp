#include "renengine_controls.hpp"

namespace ReneNgine {
	bool Controls::HandleEvents() {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return false;
				default:
					break;
				}
			}
		}

		return true;
	}
}