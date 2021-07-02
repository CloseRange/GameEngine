#pragma once
#include "Engine/Debug/Log.h"
#include "Engine/Debug/GLErrorHandle.h"
#include "UniformList.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer {
	class Shader {
	public:
		Shader(const std::string filepath);
		~Shader();
		void Bind() const;
		void Unbind() const;
		void Reload();
		void SetData(const char* name, float values[]);
	private:
		void ParseShader();
		void CreateShader();
		unsigned int CompileShader(unsigned int type, std::string& source);

		static bool HandleError(unsigned int id, unsigned int type);
		void ParseShader_CheckUniform(std::string line, UType type);

		unsigned int program;
		UniformList uniforms;
		bool isValid = false;
		bool isLoading = false;
		std::string vertexShader;
		std::string fragmentShader;
		std::string name;
		const std::string filepath;

		friend class UniformList;
	};
}

