#pragma once

#include <string>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <tiny_obj_loader.h>

#include "renengine_renderer.hpp"
#include "renengine_renderer_shader_opengl.hpp"
#include "renengine_renderer_framebuffer_opengl.hpp"
#include "renengine_renderer_model_opengl.hpp"

#include "renengine_scene.hpp"
#include "renengine_camera.hpp"

constexpr int RENENGINE_OPENGL_MAJOR_VERSION = 4;
constexpr int RENENGINE_OPENGL_MINOR_VERSION = 6;

const std::string vertex_shader_filename = "vertex.vert";
const std::string fragment_shader_filename = "fragment.frag";

namespace ReneNgine {
	namespace Rendering {
		namespace OpenGLCore {
			class RendererOpenGL : virtual public Renderer {
			public:
				RendererOpenGL(SDL_Window* window);
				~RendererOpenGL();

				RendererOpenGL(const RendererOpenGL&) = delete;
				RendererOpenGL& operator=(const RendererOpenGL&) = delete;

				RendererOpenGL(RendererOpenGL&& other) = delete;
				RendererOpenGL& operator=(RendererOpenGL&& other) = delete;

				virtual void Render(const Scene& scene, double delta_time) override;
				virtual void HandleRendererEvents(const SDL_Event& event) override;
			private:
				SDL_GLContext context;
				SDL_Window* window;
				SDL_DisplayMode display_mode;
				int window_width;
				int window_height;

				std::unique_ptr<FramebufferOpenGL> framebuffer;

				GLuint screen_vertex_buffer_object_handle;
				GLuint screen_vertex_element_array_buffer_object_handle;
				GLuint screen_vertex_array_object_handle;

				std::unique_ptr<ShaderOpenGL> screen_shader_program;
				
				std::unique_ptr<ShaderOpenGL> shader_program;

				std::unique_ptr<ModelOpenGL> model;


				void ConfigureOpenGLContext();
		
				void CreateVertexArray();
				void Cleanup() const;
			};
		}
	}
}