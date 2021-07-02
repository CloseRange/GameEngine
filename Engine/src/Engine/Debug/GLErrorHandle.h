#pragma once
#include "Engine/Debug/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer {
#ifdef LOGGING
#	define GLCall(x) GLError::Clear(); x; GLError::Check(#x, __FILE__, __LINE__)
#else
#	define GLCall(x) x
#endif



	class GLError {
	public:
#ifdef LOGGING
		static inline void Clear() { while (glGetError() != GL_NO_ERROR); }
		static inline bool Check(const char* function, const char* file, int line) {
			if (!canLog) return true;
			canLog = false;
			bool b = true;
			std::string str = file;
			std::size_t found = str.find_last_of("/\\");
			std::string fname = str.substr(found+1);


			while (GLenum error = glGetError()) {
				LOG_ERROR("[GL ERROR] {2}:{3}:{1}\n{0}", ErrorToString(error), function, fname, line);
				b = false;
			}
			return b;
		}
	private:
		static inline bool canLog = true;
		static inline std::string ErrorToString(GLenum code) {
			switch (code) {
			case GL_INVALID_ENUM: { return "[GL INVALID ENUM] Enumeration parameter is not a legal enumeration"; }
			case GL_INVALID_VALUE: { return "[GL INVALID VALUE] Value parameter is not a legal value"; }
			case GL_INVALID_OPERATION: { return "[GL INVALID OPERATION] Set of state is not legal for the parameter "; }
			case GL_STACK_OVERFLOW: { return "[GL STACK OVERFLOW] Stack pushing operation cannot be done at risk of overflowing stack's size"; }
			case GL_STACK_UNDERFLOW: { return "[GL STACK UNDERFLOW] Stack popping operation cannot be done. Stack already at its lowest point"; }
			case GL_OUT_OF_MEMORY: { return "[GL OUT OF MEMORY] Memory allocation cannot be done"; }
			case GL_INVALID_FRAMEBUFFER_OPERATION: { return "[GL INVALID FRAMEBUFFER OPERATION] Attempting to read/render to a framebuffer that is not complete"; }
			case GL_CONTEXT_LOST: { return "[GL CONTEXT LOST] OpenGL context has been lost due to a graphics card reset"; }
			default: { return "[GL ERROR] A problem has occured!"; }
			}
		}
	};
#else
		static inline void Clear() { }
		static inline bool Check(const char* function, const char* file, int line) { return true; }
	private:
		static inline std::string ErrorToString(GLenum code) { return ""; }
	};
#endif
}

