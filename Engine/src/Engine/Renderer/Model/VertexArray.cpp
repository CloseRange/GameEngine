#include "enpch.h"
#include "VertexArray.h"

namespace Renderer {
	VertexArray::VertexArray() {
		GLCall(glGenVertexArrays(1, &rendererID));
	}
	VertexArray::~VertexArray() {
		GLCall(glDeleteVertexArrays(1, &rendererID));
	}
	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexLayout& layout) {
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& e = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (const void*)offset));
			offset += e.count * LayoutElement::GetSizeOfType(e.type);
		}
	}
	void VertexArray::Bind() const {
		GLCall(glBindVertexArray(rendererID));
	}
	void VertexArray::Unbind() const {
		GLCall(glBindVertexArray(0));
	}
}

