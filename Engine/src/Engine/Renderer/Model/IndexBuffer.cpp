#include "enpch.h"
#include "IndexBuffer.h"


namespace Renderer {
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) {
		this->count = count;
		GLCall(glGenBuffers(1, &rendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}
	IndexBuffer::~IndexBuffer() {
		GLCall(glDeleteBuffers(1, &rendererID));
	}
	void IndexBuffer::Bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	}
	void IndexBuffer::Unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}
