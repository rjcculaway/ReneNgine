#pragma once

#include "renengine_resource_texture.hpp"

#include <string>
#include <GL/glew.h>

namespace ReneNgine {
	namespace Rendering {
		namespace OpenGLCore {
			class TextureOpenGL {
			public:
				TextureOpenGL(GLuint width, GLuint height);
				TextureOpenGL(TextureResource * texture_resource);

				// TextureOpenGL cannot be copied
				TextureOpenGL& operator=(const TextureOpenGL& other) = delete;
				TextureOpenGL(const TextureOpenGL& other) = delete;

				// Move
				TextureOpenGL& operator=(TextureOpenGL&& other) noexcept;
				TextureOpenGL(TextureOpenGL&& other) noexcept;

				~TextureOpenGL();
				
				TextureResource * GetTextureResource() const { return texture_resource; }
				GLuint GetTextureHandle() const { return texture_handle; }
				std::string type;
			private:
				GLuint texture_handle;
				TextureResource * texture_resource = nullptr;
			};
		}
	}
}