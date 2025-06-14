#pragma once

#include <string>

namespace ReneNgine {
	class TextureResource {
	public:
		TextureResource();
		TextureResource(const char* file_path);
		~TextureResource();

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