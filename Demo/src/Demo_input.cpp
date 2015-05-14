#include "Demo.hpp"

void Demo::manage_input(void)
{
	Engine::Input::Instance().refresh();
	if (Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_ESCAPE))
		window->stopLoop();

	// Player control
	if (Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_LSHIFT))
		camera->setSpeed(0.05f);
	else if (Engine::Input::Instance().getMouseState(SDL_BUTTON_LEFT))
		camera->setSpeed(5.0f);
	else
		camera->setSpeed(0.25f);

	camera->keyboardMove(
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_W),
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_S),
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_A),
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_D));
	camera->mouseMove(Engine::Input::Instance().getMouseRelX(), Engine::Input::Instance().getMouseRelY());
}