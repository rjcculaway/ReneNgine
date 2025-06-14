#pragma once

#include <vector>
#include "renengine_resource_texture.hpp"

namespace ReneNgine {
	class Resources {
	public:
		static std::vector<TextureResource> textures;
		static unsigned int GetCurrentTextureCount();
		static TextureResource * AddTextureResource(const char * file_path);
		Resources() = delete;
	};
}
