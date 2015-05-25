#include "Demo.hpp"

void Demo::manage_input(void)
{
	Input::InputManager::Instance().refresh();
	if (Input::InputManager::Instance().getKeyBoardState(SDL_SCANCODE_ESCAPE))
		window->stopLoop();
}