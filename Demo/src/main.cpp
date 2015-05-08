#include "Demo.hpp"

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	Engine::Renderer::Instance().init();
	Engine::Audio::Instance().init();
	Engine::Input::Instance().init();

	std::shared_ptr<Engine::Window> window(new Engine::Window("Demo OpenGL", 800, 600, GL_FALSE));
	std::shared_ptr<Demo> demo(new Demo(window));

	window->mainLoop(demo);

	return 0;
}
