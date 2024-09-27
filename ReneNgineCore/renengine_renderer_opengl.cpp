#include "renengine_renderer_opengl.hpp"

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
		CreateVertexArray();

		glViewport(0, 0, display_mode.w, display_mode.h);
		// Load sample shader
		// TODO: Load shaders dynamically depending on the model
		shader_program = std::unique_ptr<ShaderOpenGL>(new ShaderOpenGL("./vertex.vert", "./fragment.frag"));

	}

	RendererOpenGL::~RendererOpenGL() {
		Cleanup();
		SDL_GL_DeleteContext(context);
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

	void RendererOpenGL::HandleRendererEvents(const SDL_Event& event) {
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			SDL_Log("Resized window: %d × %d", event.window.data1, event.window.data2);
			window_width = event.window.data1;
			glViewport(0, 0, window_width, window_height);
		}
	}

	void RendererOpenGL::CreateVertexArray() {
		// Load model
		// TODO: Provide mechanism for loading other models

		std::string model_file_name = "cube.obj";
		tinyobj::ObjReaderConfig reader_config;
		reader_config.mtl_search_path = "./";
		reader_config.triangulate = false;

		tinyobj::ObjReader reader;
		if (!reader.ParseFromFile(model_file_name, reader_config)) {
			if (!reader.Error().empty()) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load .obj file.\n");
			}
		}

		if (!reader.Warning().empty()) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "TinyObjReader: %s\n", reader.Warning().c_str());
		}

		auto& attrib = reader.GetAttrib();
		auto& materials = reader.GetMaterials();
		auto& shapes = reader.GetShapes();

		std::vector<float> vertices = attrib.vertices;
		size_t indices_size = shapes[0].mesh.indices.size();
		std::vector<unsigned int> indices(indices_size, 0);
		for (size_t i = 0; i < indices_size; i++) {
			indices[i] = shapes[0].mesh.indices[i].vertex_index;
		}

		glGenVertexArrays(1, &vertex_array_object_handle);							// The VAO will "store" the state changes we made in the following lines
		glGenBuffers(1, &vertex_buffer_object_handle);								// Create a handle for the vertex buffer object
		glGenBuffers(1, &vertex_element_array_buffer_object_handle);
		
		glBindVertexArray(vertex_array_object_handle);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_handle);					// Tells OpenGL that the handle is for vertex positions
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);	// Actually load the data. GL_STATIC_DRAW signals intent that the buffer will be populated ONCE, and drawn multiple times
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_element_array_buffer_object_handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(
			0,			// Starting index
			3,			// How many elements does one vertex have
			GL_FLOAT,	// Data type
			GL_FALSE,
			3 * sizeof(float),
			(void*) nullptr);
		glEnableVertexAttribArray(0);	// Index 0 pertains to the vertex position, so we enable that index
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);	// Unbind array buffer
		glBindVertexArray(0);
	}

	void RendererOpenGL::Cleanup() const {
		glDeleteVertexArrays(1, &vertex_array_object_handle);
		glDeleteBuffers(1, &vertex_buffer_object_handle);
	}

	void RendererOpenGL::Render() {
		static float c = 1.0;
		glm::mat4 model = glm::identity<glm::mat4>();
		glm::mat4 projection = glm::perspective((float)glm::radians(30.0), (float)window_width / window_height, 0.1f, 150.0f);
		//glm::mat4 projection = glm::ortho(-100, 100, 100, -100);
		c += 0.01f;
		//c = fmod(c, 1.0);
		
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, c));
		model = glm::rotate(model, c, glm::vec3(0.0, 1.0, 0.0));
		//transform = glm::scale(transform, glm::vec3(c));
		glm::mat4 projection_model_matrix = projection * model;
		//std::cout << scale[0][0] << std::endl;
		//glClearColor(c, c, c, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader_program->Use();
		shader_program->SetUniformMatrix4FV("transform", projection_model_matrix);
		// Bind the buffer
		glBindVertexArray(vertex_array_object_handle);
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);
	}

}