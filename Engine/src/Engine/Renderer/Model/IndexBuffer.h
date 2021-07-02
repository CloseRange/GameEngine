#pragma once
#include "Engine/Debug/GLErrorHandle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer {
	class IndexBuffer {
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const { return count; }
	private:
		unsigned int rendererID;
		unsigned int count;

	};
}