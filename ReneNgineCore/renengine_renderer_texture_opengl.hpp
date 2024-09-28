#pragma once

#include "renengine_resource_texture.hpp"

#include <GL/glew.h>

namespace ReneNgine {
	class TextureOpenGL {
	public:
		TextureOpenGL(const char* file_path);
		~TextureOpenGL();

		GLuint GetTextureHandle() const { return texture_handle; }
	private:
		GLuint texture_handle;
	};
}