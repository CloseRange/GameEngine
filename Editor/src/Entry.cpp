#include <Engine.h>

int main() {
	Engine::Log::Init();
	auto w = new Renderer::Window(640, 480);
	return 0;
}


