#include "renengine_resource_texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ReneNgine {
	TextureResource::TextureResource() {
		this->data = nullptr;
		this->channels = 0;
		this->width = 0;
		this->height = 0;
	}
	TextureResource::TextureResource(const char* file_path) {
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(file_path, &width, &height, &channels, 0);
		path = file_path;
	}
	TextureResource::~TextureResource() {
		if (data) stbi_image_free(data);
	}
}