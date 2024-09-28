#include "renengine_renderer_texture_opengl.hpp"

#include<SDL.h>

namespace ReneNgine {
	TextureOpenGL::TextureOpenGL(const char* file_path) {
		Texture texture_resource(file_path);

		glGenTextures(1, &texture_handle);
		glBindTexture(GL_TEXTURE_2D, texture_handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (!texture_resource.GetData()) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load resource image for texture.\n");
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_resource.GetWidth(), texture_resource.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture_resource.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	TextureOpenGL::~TextureOpenGL() {
		glDeleteTextures(1, &texture_handle);
	}
}