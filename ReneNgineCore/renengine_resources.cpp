#include "renengine_resources.hpp"
#include "renengine_resource_texture.hpp"

namespace ReneNgine {
	std::vector<TextureResource> Resources::textures = std::vector<TextureResource>();
	TextureResource* Resources::AddTextureResource(const char* file_path) {
		if (textures.capacity() != 256) {
			textures.reserve(256);
		}
		textures.emplace_back(file_path);
		return &textures[textures.size() - 1];
	}
}