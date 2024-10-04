#include "renengine_engine.hpp"

namespace ReneNgine {
	void Engine::StartGameLoop() {
		const uint64_t performance_frequency = SDL_GetPerformanceFrequency();
		uint64_t last_frame_time = SDL_GetPerformanceCounter();
		double delta_time = 0.0;
		while (true) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				scene.HandleInput(event);
				renderer.HandleRendererEvents(event);
				if (event.type == SDL_QUIT) {
					return;
				}
			}

			// Update game state
			scene.HandleProcess(delta_time);

			// Render
			renderer.Render(scene, delta_time);

			uint64_t current_frame_time = SDL_GetPerformanceCounter();
			uint64_t elapsed_time = current_frame_time - last_frame_time;
			delta_time = elapsed_time / static_cast<double>(performance_frequency);
			last_frame_time = current_frame_time;
		}
	}
}