#include "Demo.hpp"

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	std::shared_ptr<Engine::Renderer> renderer(new Engine::Renderer("Demo OpenGL", 800, 600, GL_FALSE));
	std::shared_ptr<Engine::Audio> audio(new Engine::Audio);
	std::shared_ptr<Engine::Input> input(new Engine::Input);
	
	std::unique_ptr<Demo> demo(new Demo(renderer, input, audio));

	demo->launch();

	return 0;
}
