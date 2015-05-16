#include "Demo.hpp"

void Demo::manage_input(void)
{
	Engine::Input::Instance().refresh();
	if (Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_ESCAPE))
		window->stopLoop();
}