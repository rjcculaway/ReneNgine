#pragma once

#include <string>
#include <memory>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <tiny_obj_loader.h>

#include "renengine_renderer.hpp"
#include "renengine_renderer_shader_opengl.hpp"

constexpr int RENENGINE_OPENGL_MAJOR_VERSION = 4;
constexpr int RENENGINE_OPENGL_MINOR_VERSION = 6;

const std::string vertex_shader_filename = "vertex.vert";
const std::string fragment_shader_filename = "fragment.frag";

namespace ReneNgine {
	class RendererOpenGL : virtual public Renderer {
	public:
		RendererOpenGL(SDL_Window* window);
		~RendererOpenGL();
		virtual void Render() override;
		virtual void HandleRendererEvents(const SDL_Event& event) override;
	private:
		SDL_GLContext context;
		SDL_Window* window;
		SDL_DisplayMode display_mode;
		int window_width;
		int window_height;

		GLuint vertex_buffer_object_handle;
		GLuint vertex_element_array_buffer_object_handle;
		GLuint vertex_array_object_handle;
		
		std::unique_ptr<ShaderOpenGL> shader_program;
		std::unique_ptr<TextureOpenGL> texture1;
		std::unique_ptr<TextureOpenGL> texture2;

		void ConfigureOpenGLContext();
		
		void CreateVertexArray();
		void Cleanup() const;
	};
}