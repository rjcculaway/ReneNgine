#pragma once

#include <string>

namespace ReneNgine {
	class TextureResource {
	public:
		TextureResource();
		TextureResource(const char* file_path);
		~TextureResource();

		TextureResource(const TextureResource&) = delete;
		TextureResource& operator=(const TextureResource&) = delete;
		
		TextureResource(TextureResource&& other) noexcept {
			width = other.width;
			height = other.height;
			channels = other.channels;
			path = std::move(other.path);
			data = other.data;
			other.data = nullptr;
			other.width = 0;
			other.height = 0;
			other.channels = 0;
		}
		TextureResource& operator=(TextureResource&& other) noexcept {
			if (this != &other) {
				width = other.width;
				height = other.height;
				channels = other.channels;
				path = std::move(other.path);
				data = other.data;
				other.data = nullptr;
				other.width = 0;
				other.height = 0;
				other.channels = 0;
			}
			return *this;
		}

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }
		int GetChannels() const { return channels; }
		std::string GetPath() const { return path; }
		unsigned char* GetData() const { return data; }
	private:
		int width;
		int height;
		int channels;

		std::string path;
		unsigned char* data;
	};
}