#pragma once

#include "renengine_resource_shader.hpp"
#include "renengine_renderer_texture_opengl.hpp"

#include <string>
#include <unordered_map>

#include <GL/glew.h>

#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>

namespace ReneNgine {
	namespace Rendering {
		namespace OpenGLCore {
			class ShaderOpenGL : virtual public ShaderResource {
			public:
				ShaderOpenGL(const char* vertex_shader_source_path, const char* fragment_shader_source_path);
				~ShaderOpenGL();
				void Use() const;
				void SetUniform3FV(const std::string& name, glm::vec3 value);
				void SetUniformInt(const std::string& name, int value);
				void SetUniformUInt(const std::string& name, unsigned int value);
				void SetUniformFloat(const std::string& name, float value);
				void SetUniformMatrix3FV(const std::string& name, glm::mat3 value);
				void SetUniformMatrix4FV(const std::string& name, glm::mat4 value);
			private:
				GLint program_handle;

				std::unordered_map<std::string, GLint> uniform_locations{};

				GLint QueryUniformLocation(const std::string& name);

				void CompileShaderAndAttachToProgram(GLuint program_handle, const std::string& shader_text, GLenum shader_type);
				GLuint CompileShaders(const std::string& vertex_shader_source, const std::string& fragment_shader_source);
			};
		}
	}
}