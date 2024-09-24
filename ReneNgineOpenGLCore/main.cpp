#include <iostream>

#include <SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void setup() {

}

int main(int argc, char* argv[]) {
	SDL_Surface * surface = nullptr;
	SDL_Window * window = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	// Create the window
	window = SDL_CreateWindow("ReneNgine", 0, 0, display_mode.w / 2, display_mode.h / 2, SDL_WINDOW_BORDERLESS);
	
	if (!window) {
		std::cerr << "Failed to initialize window: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	// Get the window's surface
	surface = SDL_GetWindowSurface(window);

	if (!surface) {
		std::cerr << "Failed to get window surface: " << SDL_GetError() << std::endl;
	}

	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_UpdateWindowSurface(window);

	system("pause");

	// Cleanup

	// Destroy the window and its surface
	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}