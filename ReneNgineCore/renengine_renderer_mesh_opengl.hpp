#pragma once

#include <vector>
#include "renengine_vertex.hpp"
#include "renengine_renderer_texture_opengl.hpp"
#include "renengine_renderer_shader_opengl.hpp"

namespace ReneNgine {
	namespace Rendering {
		namespace OpenGLCore {
			class MeshOpenGL {
			public:
				std::vector<Vertex> vertices;
				std::vector<unsigned int> indices;
				std::vector<TextureOpenGL> textures;

				MeshOpenGL(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureOpenGL> textures);
				void Draw(ShaderOpenGL& shader);
			private:
				unsigned int vertex_array_object_handle, vertex_buffer_object_handle, element_buffer_object_handle;
				void SetupMesh();
			};
		}
	}
}