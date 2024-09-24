#include "renengine_renderer_opengl.hpp"

#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm.hpp>

namespace ReneNgine {
	RendererOpenGL::RendererOpenGL(SDL_Window* window) {
		this->window = window;
		ConfigureOpenGLContext();
		// Setup OpenGL context
		context = SDL_GL_CreateContext(window);
		if (context == NULL) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL context: %s\n", SDL_GetError());
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

		// Query and initialize available OpenGL extensions
		GLenum result = glewInit();
		if (result != GLEW_OK) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Error querying and initializing OpenGL extensions: %s\n", glewGetErrorString(result));
		}
		std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

		// Set default state of context
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glCullFace(GL_BACK); // Backface culling
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST); // Depth test to avoid overdraw
		glDisable(GL_STENCIL_TEST);
	}
	RendererOpenGL::~RendererOpenGL() {
		SDL_GL_DeleteContext(context);
	}

	void RendererOpenGL::render() {
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	void RendererOpenGL::ConfigureOpenGLContext() {
		// This engine will use OpenGL 4.5.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, RENENGINE_OPENGL_MAJOR_VERSION);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, RENENGINE_OPENGL_MINOR_VERSION);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Enable double-buffering using a 24-bit z-buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Enable VSync
		SDL_GL_SetSwapInterval(-1);
	}
}