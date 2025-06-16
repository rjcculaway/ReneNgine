#include "renengine_renderer_texture_opengl.hpp"

#include<SDL.h>

namespace ReneNgine {
	using namespace Rendering::OpenGLCore;
	TextureOpenGL::TextureOpenGL(TextureResource * texture_resource) {

		this->texture_resource= texture_resource;
		glGenTextures(1, &texture_handle);
		glBindTexture(GL_TEXTURE_2D, texture_handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (!texture_resource->GetData()) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load resource image for texture.\n");
			return;
		}

		// TODO: Fix TextureResource destructor being called
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_resource->GetWidth(), texture_resource->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture_resource->GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	/**
	* Constructor for creating a texture for use as a texture attachment for a framebuffer
	*/
	TextureOpenGL::TextureOpenGL(GLuint width, GLuint height) {
		glGenTextures(1, &texture_handle);
		glBindTexture(GL_TEXTURE_2D, texture_handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	}


	TextureOpenGL::TextureOpenGL(TextureOpenGL&& other) noexcept {
		this->texture_handle = other.texture_handle;
		this->texture_resource = other.texture_resource;
		this->type = other.type;

		other.texture_resource = nullptr;
		other.texture_handle = 0;
	}

	TextureOpenGL& TextureOpenGL::operator=(TextureOpenGL&& other) noexcept
	{
		if (this == &other) {
			return *this;
		}
		this->texture_handle = other.texture_handle;
		this->texture_resource = other.texture_resource;
		this->type = other.type;

		other.texture_resource = nullptr;
		other.texture_handle = 0;

		return *this;
	}


	TextureOpenGL::~TextureOpenGL() {
		if (texture_handle == 0) {
			return;
		}
		glDeleteTextures(1, &texture_handle);
	}
}