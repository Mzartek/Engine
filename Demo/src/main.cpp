#include "Demo.hpp"

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	srand((unsigned int)time(NULL));

	Engine::Renderer *renderer = new_ref(Engine::Renderer("Demo OpenGL", 800, 600, GL_FALSE));
	Engine::Audio *audio = new_ref(Engine::Audio);
	Engine::Input *input = new_ref(Engine::Input);

	Demo *demo = new_ref(Demo(renderer, input, audio));

	demo->launch();

	release_ref(demo);

	release_ref(input);
	release_ref(audio);
	release_ref(renderer);

	Engine::memory_state();

	return 0;
}
