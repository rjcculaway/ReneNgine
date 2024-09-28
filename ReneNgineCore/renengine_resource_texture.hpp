#pragma once


namespace ReneNgine {
	class Texture {
	public:
		Texture(const char* file_path);
		~Texture();

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