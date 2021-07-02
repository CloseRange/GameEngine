#include "enpch.h"
#include "Renderer.h"

namespace Renderer {
	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}
	void Renderer::Clear() {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void Renderer::LogDetails() {
		LOG_INFO("OpenGL Version: {0}\nVendor: {1},\nRenderer: {2}\nShading Language Version: {3}",
			glGetString(GL_VERSION),
			glGetString(GL_VENDOR),
			glGetString(GL_RENDERER),
			glGetString(GL_SHADING_LANGUAGE_VERSION));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}
}
