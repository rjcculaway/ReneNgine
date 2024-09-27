#pragma once

#include <string>

namespace ReneNgine {
	class Shader {
	public:
	protected:
		bool LoadShaderText(const char * shader_source_path, std::string& output);
	};
}