#pragma once

#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "renengine_renderer.hpp"

constexpr int RENENGINE_OPENGL_MAJOR_VERSION = 3;
constexpr int RENENGINE_OPENGL_MINOR_VERSION = 3;

const std::string vertex_shader_filename = "vertex.vert";
const std::string fragment_shader_filename = "fragment.frag";

namespace ReneNgine {
	class RendererOpenGL : virtual public Renderer {
	public:
		RendererOpenGL(SDL_Window* window, SDL_DisplayMode display_mode);
		~RendererOpenGL();
		virtual void render() override;
	private:
		SDL_GLContext context;
		SDL_Window* window;
		SDL_DisplayMode display_mode;

		GLuint vertex_buffer_object_handle;

		float vertices[9] = {
			-0.5f, -0.5f, 1.0f,
			 0.0f,  0.5f, 1.0f,
			 0.5f, -0.5f, 1.0f,
		};

		void ConfigureOpenGLContext();
		
		void CreateVertexBuffer();
		void DestroyVertexBuffer();

		bool LoadShaderText(const char* file_name, ::std::string& output);
		void LoadShaderAndAttachToProgram(GLuint program_handle, const std::string& shader_text, GLenum shader_type);
		void CompileShaders();
	};
}