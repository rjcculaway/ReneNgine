#pragma once

#include "renengine_display.hpp"
#include "renengine_controls.hpp"
#include "renengine_renderer_opengl.hpp"

namespace ReneNgine {
	class Engine {
	public:
		Display display;
		Controls controls{};
		RendererOpenGL renderer{display.window};
		void StartGameLoop();
	};
}