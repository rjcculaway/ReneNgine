#include "renengine_resource_shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL.h>

namespace ReneNgine {
	bool ShaderResource::LoadShaderText(const char* file_name, std::string& output) {
		std::ifstream file_handle;

		file_handle.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			file_handle.open(file_name);
			std::stringstream shader_text_stream{};

			shader_text_stream << file_handle.rdbuf();

			file_handle.close();

			output = shader_text_stream.str();
		}
		catch (std::ifstream::failure e) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to read file: %s\n", file_name);
			return false;
		}

		return true;
	}
}