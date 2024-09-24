#pragma once

#include "renengine_display.hpp"
#include "renengine_controls.hpp"

namespace ReneNgine {
	class Engine {
	public:
		Display display;
		Controls controls;
		void StartGameLoop();

	private:
	};
}