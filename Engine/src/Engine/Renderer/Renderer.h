#pragma once
#include "Model/VertexArray.h"
#include "Model/IndexBuffer.h"
#include "Shader/Shader.h"

#include "Engine/Debug/GLErrorHandle.h"
#include <glad/glad.h>

namespace Renderer {
	class Renderer {
	public:
		static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
		static void Clear();
		static void LogDetails();
	};
}

