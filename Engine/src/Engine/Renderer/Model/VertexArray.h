#pragma once
#include "VertexBuffer.h"
#include "Engine/Debug/GLErrorHandle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Renderer {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexLayout& layout);
		void Bind() const;
		void Unbind() const;
	private:
		unsigned int rendererID;
	};
}
