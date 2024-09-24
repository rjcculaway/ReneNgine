#pragma once

#include <SDL.h>

namespace ReneNgine {
	class Display {
	public:
		SDL_Surface* surface = nullptr;
		SDL_Window* window = nullptr;
		SDL_DisplayMode display_mode;

		Display();
		~Display();
	private:
		bool setup();
		bool cleanup();
	};
}