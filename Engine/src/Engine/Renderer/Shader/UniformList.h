#pragma once
#include "Engine/Debug/GLErrorHandle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer {
	enum class UType { VEC4, VEC3, VEC2, FLOAT, INT, SAMPLER2D };


	struct Uniform {
		int location;
		UType type;
		static inline std::string GetTypeName(UType type) {
			switch (type) {
			case UType::VEC4: return "vec4"; break;
			case UType::VEC3: return "vec3"; break;
			case UType::VEC2: return "vec2"; break;
			case UType::FLOAT: return "float"; break;
			case UType::INT: return "int"; break;
			case UType::SAMPLER2D: return "sampler2D"; break;
			default: return ""; break;
			}
		}
	};


	class UniformList {
	public:
		UniformList();
		~UniformList();
		void Push(const char* name, UType type);
		void Finilize(unsigned int program, std::string Lname);
		void SetData(const char* name, float values[]);
		void ClearList();
	private:
		std::unordered_map<std::string, Uniform> data;
	};
}

