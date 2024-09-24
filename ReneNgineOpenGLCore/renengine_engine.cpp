#include "renengine_engine.hpp"

namespace ReneNgine {
	void Engine::StartGameLoop() {
		while (true) {
			// Process inputs
			if (!controls.HandleEvents()) {
				return;
			}
			
			// Update game state

			// Render

		}
	}
}