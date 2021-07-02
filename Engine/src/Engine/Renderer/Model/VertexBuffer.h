#pragma once
#include "Engine/Debug/GLErrorHandle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer {
	class VertexBuffer {
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	private:
		unsigned int rendererID;
	};


	struct LayoutElement {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type) {
			switch (type) {
				case GL_FLOAT:			return 4; break;
				case GL_UNSIGNED_INT:	return 4; break;
				case GL_UNSIGNED_BYTE:	return 1; break;
				default: return 0;
			}
		}
	};
	class VertexLayout {
	public:
		VertexLayout() { stride = 0; }
		template<typename T> void Push(unsigned int count) { static_assert(false); }
		template<> void Push<float>(unsigned int count) {         stride += count * LayoutElement::GetSizeOfType(GL_FLOAT); elements.push_back({ GL_FLOAT, count, GL_FALSE }); }
		template<> void Push<unsigned int>(unsigned int count) {  stride += count * LayoutElement::GetSizeOfType(GL_UNSIGNED_INT); elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE }); }
		template<> void Push<unsigned char>(unsigned int count) { stride += count * LayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE); elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE }); }

		inline const std::vector<LayoutElement>& GetElements() const { return elements; }
		inline unsigned int GetStride() const { return stride; }

	private:
		std::vector<LayoutElement> elements;
		unsigned int stride;
	};

}