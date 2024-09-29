#include "renengine_renderer_framebuffer_opengl.hpp"

#include <SDL.h>

namespace ReneNgine {
	using namespace Rendering::OpenGLCore;
	FramebufferOpenGL::FramebufferOpenGL(unsigned int width, unsigned int height) {
		glGenFramebuffers(1, &framebuffer_handle);
		CreateAttachments(width, height);
	}

	FramebufferOpenGL::~FramebufferOpenGL() {
		glDeleteTextures(1, &color_attachment_handle);
		glDeleteTextures(1, &depth_and_stencil_attachment_handle);
		glDeleteFramebuffers(1, &framebuffer_handle);
	}

	void FramebufferOpenGL::CreateAttachments(const unsigned int width, const unsigned int height) {
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_handle);

		// Setup color attachment
		glGenTextures(1, &color_attachment_handle);
		glBindTexture(GL_TEXTURE_2D, color_attachment_handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			color_attachment_handle, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Setup depth and stencil attachment
		glGenRenderbuffers(1, &depth_and_stencil_attachment_handle);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_and_stencil_attachment_handle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_and_stencil_attachment_handle);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unsuccessfully created framebuffer: %s\n", glewGetErrorString(glCheckFramebufferStatus(GL_FRAMEBUFFER)));
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FramebufferOpenGL::ResizeAttachments(const unsigned int width, const unsigned int height) {
		glDeleteTextures(1, &color_attachment_handle);
		glDeleteTextures(1, &depth_and_stencil_attachment_handle);

		CreateAttachments(width, height);
	}
}