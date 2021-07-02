#include "enpch.h"
#include "UniformList.h"


namespace Renderer {
	UniformList::UniformList() {
	}
	UniformList::~UniformList() {
	}
	void UniformList::Push(const char* name, UType type) {
		data[name] = { -1, type };
		// LOG_WARN("adding uniform {0} {1};", Uniform::GetTypeName(type), name);
	}
	void UniformList::Finilize(unsigned int program, std::string Lname) {
		for (auto& e : data) {
			std::string name = e.first;
			Uniform u = e.second;
			GLCall(int location = glGetUniformLocation(program, name.c_str()));
			if (location == -1)
				LOG_ERROR("[{2}] Coudn't find uniform {0} {1};", Uniform::GetTypeName(u.type), name, Lname);
			else {
				data[name].location = location;

				// GLCall(glUniform4f(location, 0.8f, 0.3f, 0.7f, 1.0f));
			}
		}
	}
	void UniformList::SetData(const char* name, float values[]) {
		Uniform u = data[name];
		switch (u.type) {
			case UType::VEC4: 
				GLCall(glUniform4f(u.location, values[0], values[1], values[2], values[3]));
				break; 
			case UType::VEC3:
				GLCall(glUniform3f(u.location, values[0], values[1], values[2]));
				break; 
			case UType::VEC2:
				GLCall(glUniform2f(u.location, values[0], values[1]));
				break;
			case UType::FLOAT:
				GLCall(glUniform1f(u.location, values[0]));
				break;
			case UType::INT:
				GLCall(glUniform1i(u.location, (int)values[0]));
				break;
			case UType::SAMPLER2D:
				GLCall(glUniform1i(u.location, (int)values[0]));
				break;
		}
	}
	void UniformList::ClearList() {
		data.clear();
	}
}

