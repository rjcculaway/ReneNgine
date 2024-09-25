#pragma once

#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "renengine_renderer.hpp"

constexpr int RENENGINE_OPENGL_MAJOR_VERSION = 4;
constexpr int RENENGINE_OPENGL_MINOR_VERSION = 6;

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
		GLuint vertex_array_object_handle;
		GLuint shader_program_handle;

		void ConfigureOpenGLContext();
		
		void CreateVertexArray();
		void Cleanup();

		bool LoadShaderText(const char* file_name, ::std::string& output);
		void LoadShaderAndAttachToProgram(GLuint program_handle, const std::string& shader_text, GLenum shader_type);
		GLuint CompileShaders();
	};
}