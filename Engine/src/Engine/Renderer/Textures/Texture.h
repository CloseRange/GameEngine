#pragma once
#include "Engine/Renderer/Renderer.h"

namespace Renderer {
	class Texture {
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }
	private:
		unsigned int rendererID;
		std::string filepath;
		unsigned char* localBuffer;
		int width, height, bpp;
	};
}
