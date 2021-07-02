#include "enpch.h"
#include "Window.h"
#include "Shader/Shader.h"

#include "Model/VertexBuffer.h"
#include "Model/IndexBuffer.h"
#include "Model/VertexArray.h"
#include "Textures/Texture.h"
#include "Renderer.h"

#include <math.h>
namespace Renderer {
	Window::Window(int width, int height, const char* name) {
		if (!glfwInit()) {
			isValid = -1;
			LOG_ERROR("Could not initilize Window '{0}'\nError code {1}: GLFW has not been initalized", name, isValid);
			return;
		}


		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, name, NULL, NULL);
		if (!window) {
			glfwTerminate();
			isValid = -2;
			LOG_ERROR("Could not initilize Window '{0}'\nError code {1}: window failed to create", name, isValid);
			return;
		}
		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);
		{


			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			LOG_FATAL(status, "Failed to initalize ModernGL with Glad!");
			Renderer::LogDetails();

			float vertices[] = {
				-0.5f, -0.5f, 0.0f, 0.0f,
				 0.5f, -0.5f, 1.0f, 0.0f,
				 0.5f,  0.5f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f
			};
			unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

			VertexArray va;
			VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

			VertexLayout layout;
			layout.Push<float>(2);
			layout.Push<float>(2);
			va.AddBuffer(vb, layout);


			IndexBuffer ib(indices, 6);


			Shader shader("res/shaders/Base.shader");

			Texture texture("res/textures/taco.png");
			texture.Bind();
			float texI[] = { 0.0f };
			shader.SetData("u_Texture", texI);

			va.Unbind();
			vb.Unbind();
			shader.Unbind();
			ib.Unbind();

			int s = 0;

			while (!glfwWindowShouldClose(window)) {

				s++;
				float r = (sin(s / 10.0f) + 1.0f) / 2.0f;
				float g = (cos(s / 10.0f) + 1.0f) / 2.0f;
				float b = (tan(s / 10.0f) + 1.0f) / 2.0f;

				float t[] = { r, g, .5f };
				shader.SetData("u_Color", t);
				Renderer::Clear();
				Renderer::Draw(va, ib, shader);


				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		}
		glfwTerminate();
	}
	Window::~Window() {
		delete window;
	}
}
