#pragma once

#include <SDL.h>

constexpr int RENENGINE_OPENGL_MAJOR_VERSION = 4;
constexpr int RENENGINE_OPENGL_MINOR_VERSION = 5;

namespace ReneNgine {
	class RendererOpenGL {
	public:
		RendererOpenGL(SDL_Window* window);
		~RendererOpenGL();
		void render();
	private:
		SDL_GLContext context;
		void ConfigureOpenGLContext();
		SDL_Window* window;
	};
}