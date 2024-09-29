#pragma once

#include "renengine_renderer_texture_opengl.hpp"

#include <memory>

#include <GL/glew.h>

namespace ReneNgine {
	namespace Rendering {
		namespace OpenGLCore {
			class FramebufferOpenGL
			{
			public:
				FramebufferOpenGL(unsigned int width, unsigned int height);
				~FramebufferOpenGL();
				void CreateAttachments(const unsigned int width, const unsigned int height);
				void ResizeAttachments(unsigned int width, unsigned int height);
				GLuint GetFramebufferHandle() const { return framebuffer_handle; }
				GLuint GetColorAttachment() const { return color_attachment_handle; }
				GLuint GetDepthAndStencilAttachment() const { return depth_and_stencil_attachment_handle; }
			private:
				GLuint framebuffer_handle;
				GLuint color_attachment_handle;
				GLuint depth_and_stencil_attachment_handle;
			};
		}
	}
}

