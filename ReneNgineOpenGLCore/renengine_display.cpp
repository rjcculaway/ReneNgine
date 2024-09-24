#include "renengine_display.hpp"

#include <iostream>

namespace ReneNgine {
	Display::Display() {
		setup();
	}

	Display::~Display() {
		cleanup();
	}

	bool Display::setup() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
			return false;
		}

		SDL_GetCurrentDisplayMode(0, &display_mode);
		// Create the window
		window = SDL_CreateWindow("ReneNgine", 0, 0, display_mode.w / 2, display_mode.h / 2, SDL_WINDOW_BORDERLESS);

		if (!window) {
			std::cerr << "Failed to initialize window: " << SDL_GetError() << std::endl;
			return false;
		}

		// Get the window's surface
		surface = SDL_GetWindowSurface(window);

		if (!surface) {
			std::cerr << "Failed to get window surface: " << SDL_GetError() << std::endl;
		}
		return true;
	}

	bool Display::cleanup() {
		// Destroy the window and its surface
		SDL_DestroyWindow(window);

		SDL_Quit();

		return true;
	}
}