#include "enpch.h"
#include "VertexBuffer.h"


namespace Renderer {
	VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
		GLCall(glGenBuffers(1, &rendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}
	VertexBuffer::~VertexBuffer() {
		GLCall(glDeleteBuffers(1, &rendererID));
	}
	void VertexBuffer::Bind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	}
	void VertexBuffer::Unbind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}
