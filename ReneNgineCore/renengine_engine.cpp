#include "renengine_engine.hpp"

namespace ReneNgine {
	void Engine::StartGameLoop() {
		uint64_t last_frame_time = SDL_GetTicks64();
		while (true) {
			uint64_t current_frame_time = SDL_GetTicks64();
			uint64_t delta_time = current_frame_time - last_frame_time;

			float seconds_per_frame = 1.0f / display.GetFPS();

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
			renderer.Render(scene, current_frame_time);

		}
	}
}