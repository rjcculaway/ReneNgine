#include "renengine_engine.hpp"

namespace ReneNgine {
	void Engine::StartGameLoop() {
		uint64_t last_frame_time = SDL_GetTicks64();
		while (true) {
			uint64_t current_frame_time = SDL_GetTicks64();
			uint64_t delta_time = current_frame_time - last_frame_time;

			float seconds_per_frame = 1.0f / display.GetFPS();
			// Process inputs
			if (!controls.HandleEvents()) {
				return;
			}
			
			// Update game state

			// Render
			renderer.render();

		}
	}
}