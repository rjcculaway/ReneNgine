#include "renengine_renderer_opengl.hpp"
#include "renengine_vertex.hpp"

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <SDL.h>

#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace ReneNgine {
	using namespace Rendering::OpenGLCore;
	RendererOpenGL::RendererOpenGL(SDL_Window* window) {
		this->window = window;
		SDL_GetCurrentDisplayMode(0, &this->display_mode);
		SDL_GetWindowSize(window, &window_width, &window_height);

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
		SDL_Log("Using GLEW %s\n", glewGetString(GLEW_VERSION));

		// Set default state of context
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		// Culling
		glFrontFace(GL_CW);			// Expect clockwise winding order for culling
		glEnable(GL_CULL_FACE);		// Culling
		glCullFace(GL_BACK);		// Backface culling

		glEnable(GL_DEPTH_TEST);	// Depth test to avoid overdraw
		glDisable(GL_STENCIL_TEST);

		// Setup buffers
		model = std::make_unique<ModelOpenGL>("./assets/backpack/backpack.obj");
		CreateVertexArray();

		framebuffer = std::make_unique<FramebufferOpenGL>(window_width, window_height);

		glViewport(0, 0, window_width, window_width);
		// Load sample shader
		// TODO: Load shaders dynamically depending on the model
		shader_program = std::unique_ptr<ShaderOpenGL>(new ShaderOpenGL("./vertex.vert", "./fragment.frag"));

		// Load shader for displaying framebuffers in the screen
		screen_shader_program = std::unique_ptr<ShaderOpenGL>(new ShaderOpenGL("./screen_vertex.vert", "./screen_fragment.frag"));

	}

	RendererOpenGL::~RendererOpenGL() {
		Cleanup();
		SDL_GL_DeleteContext(context);
	}

	void RendererOpenGL::ConfigureOpenGLContext() {
		// This engine will use OpenGL 4.6.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, RENENGINE_OPENGL_MAJOR_VERSION);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, RENENGINE_OPENGL_MINOR_VERSION);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Enable double-buffering using a 24-bit z-buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Enable VSync
		SDL_GL_SetSwapInterval(-1);
	}

	void RendererOpenGL::HandleRendererEvents(const SDL_Event& event) {
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			SDL_Log("Resized window: %d × %d", event.window.data1, event.window.data2);
			window_width = event.window.data1;
			window_height = event.window.data2;
			framebuffer->ResizeAttachments(window_width, window_height);
			
			glViewport(0, 0, window_width, window_height);
		}
	}

	
	void RendererOpenGL::CreateVertexArray() {
		// Setup buffers for screen quads
		float screen_vertices[] = {
			// Position   // Texture Coordinates
			-1.0f, -1.0f,  0.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f,  1.0f,  1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
		};


		glGenVertexArrays(1, &screen_vertex_array_object_handle);							
		glGenBuffers(1, &screen_vertex_buffer_object_handle);								

		glBindVertexArray(screen_vertex_array_object_handle);
		glBindBuffer(GL_ARRAY_BUFFER, screen_vertex_buffer_object_handle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(screen_vertices), screen_vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));

		glEnableVertexAttribArray(0);	// Index 0 pertains to the vertex position, so we enable that index
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

	}
	

	void RendererOpenGL::Cleanup() const {
		//glDeleteVertexArrays(1, &vertex_array_object_handle);
		//glDeleteBuffers(1, &vertex_buffer_object_handle);
		glDeleteVertexArrays(1, &screen_vertex_array_object_handle);
		glDeleteBuffers(1, &screen_vertex_buffer_object_handle);
	}

	void RendererOpenGL::Render(const Scene& scene, double delta_time) {
		static double c = 25.0;
		static double time_elapsed = 0.0;
		glm::vec3 light_position = glm::normalize(glm::vec3(
			0.0, 15.0, 15.0
		));
		glm::mat4 model_matrix = glm::identity<glm::mat4>();
		glm::mat4 projection_matrix = glm::perspective((float)glm::radians(30.0), (float)window_width / window_height, 0.1f, 150.0f);
		//glm::mat4 projection = glm::ortho(-100, 100, 100, -100);
		c += 1.0f * delta_time;
		time_elapsed += delta_time;
		//c = fmod(c, 1.0);
		
		model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, 15.0));
		model_matrix = glm::rotate(model_matrix, static_cast<float>(c), glm::vec3(0.0, 1.0, 0.0));
		//model = glm::scale(model, glm::vec3(0.5 + c));
		glm::mat4 projection_model_matrix = projection_matrix * model_matrix;
		glm::mat3 normal_matrix = glm::mat3(glm::transpose(glm::inverse(model_matrix)));
		
		auto active_camera = scene.GetActiveCamera();
		// First pass: Render Scene to framebuffer

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetFramebufferHandle());
		
		shader_program->Use();
		// Positions
		shader_program->SetUniform3FV("light_position", light_position);
		shader_program->SetUniform3FV("light_color", glm::vec3(1.0, 1.0, 0.95));
		if (active_camera) {
			shader_program->SetUniform3FV("view_position", active_camera->transform.position);
		}

		// Matrices
		shader_program->SetUniformMatrix3FV("normal_matrix", normal_matrix);
		shader_program->SetUniformMatrix4FV("model_matrix", model_matrix);
		if (active_camera) {
			shader_program->SetUniformMatrix4FV("view_matrix", active_camera->GetViewMatrix());
		}
		shader_program->SetUniformMatrix4FV("projection_matrix", projection_matrix);
		
		
		shader_program->SetUniformFloat("c", static_cast<float>(c));
		shader_program->SetUniformFloat("time", static_cast<float>(time_elapsed));
		
		// Texture Samplers
		shader_program->SetUniformInt("texture_sampler1", 0);
		shader_program->SetUniformInt("texture_sampler2", 1);

		// Phong Lighting Model Properties
		shader_program->SetUniformFloat("shininess", 32.0);
		shader_program->SetUniform3FV("ambient", glm::vec3(0.2, 0.32, 0.448));
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model->Draw(*shader_program);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Second pass: Render the attachments
		screen_shader_program->Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, framebuffer->GetColorAttachment());
		shader_program->SetUniformInt("screen_texture", 0);

		glBindVertexArray(screen_vertex_array_object_handle);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);

		SDL_GL_SwapWindow(window);
	}
}