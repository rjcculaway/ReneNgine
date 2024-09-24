#include <iostream>

#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>

int main(int argc, char * argv[]) {
	SDL_Surface* window_surface = nullptr;
	SDL_Window* window = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	window = SDL_CreateWindow("ReneNgine", 0, 0, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

	return 0;
}