#pragma once


namespace ReneNgine {
	class TextureResource {
	public:
		TextureResource(const char* file_path);
		~TextureResource();

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }
		int GetChannels() const { return channels; }
		unsigned char* GetData() const { return data; }
	private:
		int width;
		int height;
		int channels;

		unsigned char* data;
	};
}