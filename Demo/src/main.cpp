#include "Demo.hpp"

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	srand((unsigned int)time(NULL));

	Engine::Renderer *renderer = new Engine::Renderer("Demo OpenGL", 800, 600, GL_FALSE);
	Engine::Audio *audio = new Engine::Audio;
	Engine::Input *input = new Engine::Input;

	Demo *demo = new Demo(renderer, input, audio);
	
	demo->launch();

	delete demo;

	delete input;
	delete audio;
	delete renderer;

	std::cout << "MemState " << Engine::Object::getMemoryState() << std::endl;

	return 0;
}
