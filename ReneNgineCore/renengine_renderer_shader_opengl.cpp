#include "renengine_renderer_shader_opengl.hpp"

#include <SDL.h>

#define GLM_FORCE_LEFT_HANDED
#include <glm/gtc/type_ptr.hpp>

namespace ReneNgine {
	ShaderOpenGL::ShaderOpenGL(const char* vertex_shader_source_path, const char* fragment_shader_source_path) {
		std::string vertex_shader_source; 
		std::string fragment_shader_source;

		LoadShaderText(vertex_shader_source_path, vertex_shader_source);
		LoadShaderText(fragment_shader_source_path, fragment_shader_source);

		program_handle = CompileShaders(vertex_shader_source, fragment_shader_source);
	}

	ShaderOpenGL::~ShaderOpenGL() {
		glUseProgram(0);
		glDeleteProgram(program_handle);
	}

	GLuint ShaderOpenGL::CompileShaders(const std::string& vertex_shader_source, const std::string& fragment_shader_source) {
		GLuint program_handle = glCreateProgram();

		if (program_handle == 0) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to create shader program handle\n");
			return 0;
		}

		CompileShaderAndAttachToProgram(program_handle, vertex_shader_source, GL_VERTEX_SHADER);
		CompileShaderAndAttachToProgram(program_handle, fragment_shader_source, GL_FRAGMENT_SHADER);

		GLint program_status = 0;
		GLchar program_log[1024] = { 0 };

		glLinkProgram(program_handle);
		glGetProgramiv(program_handle, GL_LINK_STATUS, &program_status);
		if (!program_status) {
			glGetProgramInfoLog(program_handle, sizeof(program_log), NULL, program_log);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to link shader program: %s\n", program_log);
		}

		glValidateProgram(program_handle);
		glGetProgramiv(program_handle, GL_VALIDATE_STATUS, &program_status);
		if (!program_status) {
			glGetProgramInfoLog(program_handle, sizeof(program_log), NULL, program_log);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Invalid shader program: %s\n", program_log);
		}

		return program_handle;
	}

	void ShaderOpenGL::CompileShaderAndAttachToProgram(GLuint program_handle, const std::string& shader_text, GLenum shader_type) {
		GLuint shader_handle = glCreateShader(shader_type);

		if (shader_handle == 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create handle for shader type %d.\n", shader_type);
		}

		// Set the source string
		const GLchar* sources[1] = {};
		sources[0] = shader_text.c_str();

		GLint source_lengths[1] = {};
		source_lengths[0] = (GLint)shader_text.size();

		glShaderSource(shader_handle, 1, sources, source_lengths);

		// Compile the shader
		glCompileShader(shader_handle);

		GLint compile_status = 0;
		glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);

		if (!compile_status) {
			GLchar info_log[1024];
			glGetShaderInfoLog(shader_handle, 1024, NULL, info_log);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to compile shader for shader type %d: %s\n", shader_type, info_log);
		}

		// Attach the shader
		glAttachShader(program_handle, shader_handle);

		// Delete the shader handle as it is no longer needed
		glDeleteShader(shader_handle);
	}

	void ShaderOpenGL::Use() const {
		glUseProgram(program_handle);
	}


	GLint ShaderOpenGL::QueryUniformLocation(const std::string& name) {
		// Query the location of our uniform
		if (uniform_locations.find(name) == uniform_locations.end()) {
			GLint uniform_location = glGetUniformLocation(program_handle, name.c_str());
			if (uniform_location == -1) {
				//SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Failed to query uniform location.\n");
				return -1;
			}
			uniform_locations[name] = uniform_location;
		}
		return uniform_locations[name];
	}

	void ShaderOpenGL::SetUniform3FV(const std::string& name, glm::vec3 value) {
		GLint location = QueryUniformLocation(name);
		glUniform3fv(location, 1, glm::value_ptr(value));
	}
	
	void ShaderOpenGL::SetUniformInt(const std::string& name, int value) {
		GLint location = QueryUniformLocation(name);
		glUniform1i(location, value);
	}

	void ShaderOpenGL::SetUniformFloat(const std::string& name, float value) {
		GLint location = QueryUniformLocation(name);
		glUniform1fv(location, 1, &value);
	}

	void ShaderOpenGL::SetUniformMatrix3FV(const std::string& name, glm::mat3 value) {
		GLint location = QueryUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderOpenGL::SetUniformMatrix4FV(const std::string& name, glm::mat4 value) {
		GLint location = QueryUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

}