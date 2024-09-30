#pragma once

#include "renengine_display.hpp"
#include "renengine_renderer_opengl.hpp"

#include "renengine_scene.hpp" 

namespace ReneNgine {
	class Engine {
	public:
		void StartGameLoop();
	private:
		Scene scene;
		Display display;
		Rendering::OpenGLCore::RendererOpenGL renderer{display.window};
	};
}