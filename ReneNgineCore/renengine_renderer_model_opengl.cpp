#include "renengine_renderer_model_opengl.hpp"
#include "renengine_resource_texture.hpp"
#include "renengine_resources.hpp"
#include <SDL.h>
#define GLM_FORCE_LEFT_HANDED
#include <glm/vec3.hpp>

namespace ReneNgine {
	namespace Rendering {
		namespace OpenGLCore {
			void ModelOpenGL::Draw(ShaderOpenGL& shader) {
				for (unsigned int i = 0; i < meshes.size(); i++) {
					meshes[i].Draw(shader);
				}
			}
			void ModelOpenGL::LoadModel(std::string path) {
				Assimp::Importer importer;
				const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

				if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", importer.GetErrorString());
					return;
				}

				directory = path.substr(0, path.find_last_of('/'));

				ProcessNode(scene->mRootNode, scene);

			}
			void ModelOpenGL::ProcessNode(aiNode* node, const aiScene* scene) {
				// Process all of the node's meshes
				for (unsigned int i = 0; i < node->mNumMeshes; i++) {
					aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
					meshes.push_back(ProcessMesh(mesh, scene));
				}
				for (unsigned int i = 0; i < node->mNumChildren; i++) {
					ProcessNode(node->mChildren[i], scene);
				}

			}
			MeshOpenGL ModelOpenGL::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
				std::vector<Vertex> vertices;
				std::vector<unsigned int> indices;
				std::vector<TextureOpenGL> textures;

				// Process position, normal, texture coordinate
				for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
					Vertex vertex;
					glm::vec3 position;
					position.x = mesh->mVertices[i].x;
					position.y = mesh->mVertices[i].y;
					position.z = mesh->mVertices[i].z;
					vertex.position = position;

					glm::vec3 normal;
					normal.x = mesh->mNormals[i].x;
					normal.y = mesh->mNormals[i].y;
					normal.z = mesh->mNormals[i].z;
					vertex.normal = normal;

					// A mesh can have up to 8 texture coordinates per vertex, but this is optional so we have to do some checks.
					if (mesh->mTextureCoords[0]) {
						// We only use the first texture coordinate for now
						glm::vec2 texture_coordinates;
						texture_coordinates.x = mesh->mTextureCoords[0][i].x;
						texture_coordinates.y = mesh->mTextureCoords[0][i].y;
						vertex.texture_coordinates = texture_coordinates;
					}
					else {
						vertex.texture_coordinates = glm::vec2(0.0f, 0.0f);
					}

					vertices.push_back(vertex);
				}

				// Process indices
				for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
					aiFace face = mesh->mFaces[i];
					for (unsigned int j = 0; j < face.mNumIndices; j++) {
						indices.push_back(face.mIndices[j]);
					}
				}

				// Process materials
				if (mesh->mMaterialIndex >= 0) {
					aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
					std::vector<TextureOpenGL> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
					textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

					std::vector<TextureOpenGL> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
					textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
				}
				return MeshOpenGL(vertices, indices, textures);
			}
			std::vector<TextureOpenGL> ModelOpenGL::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name) {
				std::vector<TextureOpenGL> textures;
				textures.reserve(mat->GetTextureCount(type));
				for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
					aiString str;
					mat->GetTexture(type, i, &str);

					bool skip = false;

					for (auto& texture_resource : Resources::textures) {
						if (std::strcmp(texture_resource.GetPath().c_str(), str.C_Str()) == 0) {
							skip = true;
							break;
						}
					}

					if (!skip) {
						size_t current = Resources::textures.size();

						//TextureOpenGL texture(Resources::AddTextureResource("./assets/painted_concrete_diff_1k.jpg"));
						textures.emplace_back(Resources::AddTextureResource(str.C_Str()));
					}
				}
				return textures;
			}
		}
	}
}