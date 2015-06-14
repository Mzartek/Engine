#include "Demo.hpp"

void Demo::manage_input(void)
{
		inputManager.refresh();

		if (inputManager.getKeyBoardState(SDL_SCANCODE_ESCAPE))
				window->stopLoop();

		if (inputManager.getKeyBoardState(SDL_SCANCODE_LSHIFT))
				camera->setSpeed(0.05f);
		else if (inputManager.getMouseState(SDL_BUTTON_LEFT))
				camera->setSpeed(5.0f);
		else
				camera->setSpeed(0.25f);

		camera->keyboardMove(
				inputManager.getKeyBoardState(SDL_SCANCODE_W),
				inputManager.getKeyBoardState(SDL_SCANCODE_S),
				inputManager.getKeyBoardState(SDL_SCANCODE_A),
				inputManager.getKeyBoardState(SDL_SCANCODE_D)
				);
		camera->mouseMove(
				inputManager.getMouseRelX(),
				inputManager.getMouseRelY());
}