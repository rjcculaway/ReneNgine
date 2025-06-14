#include "renengine_renderer_mesh_opengl.hpp"

namespace ReneNgine {
	using namespace Rendering::OpenGLCore;
	MeshOpenGL::MeshOpenGL(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureOpenGL> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		SetupMesh();
	}

	void MeshOpenGL::Draw(ShaderOpenGL& shader) {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.SetUniformInt(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].GetTextureHandle());
		}
		glActiveTexture(GL_TEXTURE0);

		// draw mesh
		glBindVertexArray(vertex_array_object_handle);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void MeshOpenGL::SetupMesh() {
		glGenVertexArrays(1, &vertex_array_object_handle);
		glGenBuffers(1, &vertex_buffer_object_handle);
		glGenBuffers(1, &element_buffer_object_handle);

		glBindVertexArray(vertex_array_object_handle);
		
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_handle);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) nullptr);
		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
		// Vertex Texture Coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)offsetof(Vertex, texture_coordinates)
		);

		glBindVertexArray(0);
	}
}