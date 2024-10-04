#include "renengine_display.hpp"

#include <iostream>

namespace ReneNgine {
	Display::Display() {
		setup();
	}

	Display::~Display() {
		Cleanup();
	}

	bool Display::setup() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s\n", SDL_GetError());
			return false;
		}

		SDL_GetCurrentDisplayMode(0, &display_mode);
		std::cout << display_mode.w << " x " << display_mode.h << std::endl;
		fps = display_mode.refresh_rate;
		// Create the window
		window = SDL_CreateWindow("ReneNgine", 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			800, 600, 
			SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);


		if (!window) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize window: %s\n", SDL_GetError());
			return false;
		}

		// Get the window's surface
		surface = SDL_GetWindowSurface(window);

		if (!surface) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to get window surface: %s\n", SDL_GetError());
		}

		// Capture mouse
		SDL_SetRelativeMouseMode(SDL_TRUE);

		return true;
	}

	bool Display::Cleanup() {
		// Destroy the window and its surface
		SDL_DestroyWindow(window);

		SDL_Quit();

		return true;
	}
}