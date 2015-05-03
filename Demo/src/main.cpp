#include "Demo.hpp"

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	srand((unsigned int)time(NULL));

	Engine::Renderer *renderer = new_ptr(Engine::Renderer("Demo OpenGL", 800, 600, GL_FALSE));
	Engine::Audio *audio = new_ptr(Engine::Audio);
	Engine::Input *input = new_ptr(Engine::Input);

	Demo *demo = new_ptr(Demo(renderer, input, audio));

	demo->launch();

	release_ptr(demo);

	release_ptr(input);
	release_ptr(audio);
	release_ptr(renderer);

	Engine::memory_state();

	return 0;
}
