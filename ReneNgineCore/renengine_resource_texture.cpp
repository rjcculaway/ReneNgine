#include "renengine_resource_texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ReneNgine {
	Texture::Texture(const char* file_path) {
		data = stbi_load(file_path, &width, &height, &channels, 0);
	}
	Texture::~Texture() {
		stbi_image_free(data);
	}
}