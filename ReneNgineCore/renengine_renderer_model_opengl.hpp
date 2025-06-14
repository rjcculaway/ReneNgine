#pragma once
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "renengine_resources.hpp"
#include "renengine_renderer_mesh_opengl.hpp"
#include "renengine_renderer_shader_opengl.hpp"

namespace ReneNgine {
	namespace Rendering {
		namespace OpenGLCore {
			class ModelOpenGL {
			public:
				ModelOpenGL(const char* path) {
					LoadModel(path);
				}
				void Draw(ShaderOpenGL& shader);

			private:
				std::vector<MeshOpenGL> meshes;
				std::string directory;

				void LoadModel(std::string path);
				void ProcessNode(aiNode* node, const aiScene* scene);
				MeshOpenGL ProcessMesh(aiMesh* mesh, const aiScene* scene);
				std::vector<TextureOpenGL> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
			};
		}
	}
}