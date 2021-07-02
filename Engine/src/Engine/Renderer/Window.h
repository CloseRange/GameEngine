#pragma once
#include "Engine/Debug/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer {
	class Window {
	public:
		Window(int width, int height, const char* name="New Window");
		~Window();
		inline int IsValid() const { return isValid; }
	private:
		GLFWwindow* window;
		int isValid = 1;

	};
}
