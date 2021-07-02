#include "enpch.h"
#include "Shader.h"


namespace Renderer {

	Shader::Shader(const std::string filepath) : filepath(filepath) {
		{
			struct stat buffer;
			bool exists = (stat(filepath.c_str(), &buffer) == 0);
			if (!exists) LOG_ERROR("Unable to find file '{0}'", filepath);
		}
		ParseShader();
		CreateShader();
		uniforms.Finilize(program, name);
	}
	Shader::~Shader() {
		GLCall(glDeleteProgram(program));
	}
	void Shader::Reload() {
		if (isValid) {
			GLCall(glDeleteProgram(program));
		}
		{
			struct stat buffer;
			bool exists = (stat(filepath.c_str(), &buffer) == 0);
			if (!exists) LOG_ERROR("Unable to find file '{0}'", filepath);
		}
		isLoading = true;
		isValid = false;
		uniforms.ClearList();
		ParseShader();
		CreateShader();
		uniforms.Finilize(program, name);
		isLoading = false;
	}
	void Shader::Bind() const {
		if (!isValid) {
			LOG_ERROR("Failed to bind invalid Shader{0}", (name == "" ? ("") : (": '" + name + "'")));
			return;
		}
		if (isLoading) {
			Unbind();
			return;
		}
		GLCall(glUseProgram(program));
	}
	void Shader::Unbind() const {
		GLCall(glUseProgram(0));
	}
	void Shader::SetData(const char* name, float values[]) {
		uniforms.SetData(name, values);
	}
	void Shader::CreateShader() {
		GLCall(program = glCreateProgram());
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		isValid = (vs != 0 && fs != 0);

		if (isValid) {
			GLCall(glAttachShader(program, vs));
			GLCall(glAttachShader(program, fs));
			GLCall(glLinkProgram(program));
			GLCall(glValidateProgram(program));
		}
		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

	}
	unsigned int Shader::CompileShader(unsigned int type, std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		if (HandleError(id, type)) return 0;

		return id;
	}
	bool Shader::HandleError(unsigned int id, unsigned int type) {
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			LOG_ERROR("Failed to compile {1} shader!\n{0}", message, type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			glDeleteShader(id);
			return true;
		}
		return false;
	}

	void Shader::ParseShader() {
		std::ifstream stream(filepath);

		enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line)) {
			std::size_t pos = line.find("#name");
			if (pos != std::string::npos) {
				name = line.substr(pos + 6);
				continue;
			}
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				} else if (line.find("fragment") != std::string::npos) {
					type = ShaderType::FRAGMENT;
				}
				continue;
			}
			if (line.find("uniform") != std::string::npos) {
				ParseShader_CheckUniform(line, UType::VEC4);
				ParseShader_CheckUniform(line, UType::VEC3);
				ParseShader_CheckUniform(line, UType::VEC2);
				ParseShader_CheckUniform(line, UType::FLOAT);
				ParseShader_CheckUniform(line, UType::INT);
				ParseShader_CheckUniform(line, UType::SAMPLER2D);
			}
			if(type != ShaderType::NONE)
				ss[(int)type] << line << '\n';
		}
		vertexShader = ss[0].str();
		fragmentShader = ss[1].str();
	}

	void Shader::ParseShader_CheckUniform(std::string line, UType type) {
		std::string typeName = Uniform::GetTypeName(type);
		std::size_t pos = line.find(" " + typeName + " ");
		if (pos != std::string::npos) {
			std::string nm = line.substr(pos + typeName.length() + 2);
			std::size_t semiPos = nm.find(";");
			std::string nname = nm.substr(0, semiPos);
			uniforms.Push(nname.c_str(), type);
		}
	}
}
