#include "Demo.hpp"

void Demo::manage_input(void)
{
	Input::InputHandler::Instance().refresh();

	if (Input::InputHandler::Instance().getKeyBoardState(SDL_SCANCODE_ESCAPE))
		Graphics::GraphicsRenderer::Instance().stopLoop();

	if (Input::InputHandler::Instance().getKeyBoardState(SDL_SCANCODE_LSHIFT))
		camera->setSpeed(0.05f);
	else if (Input::InputHandler::Instance().getMouseState(SDL_BUTTON_LEFT))
		camera->setSpeed(5.0f);
	else
		camera->setSpeed(0.25f);

	camera->keyboardMove(
		Input::InputHandler::Instance().getKeyBoardState(SDL_SCANCODE_W),
		Input::InputHandler::Instance().getKeyBoardState(SDL_SCANCODE_S),
		Input::InputHandler::Instance().getKeyBoardState(SDL_SCANCODE_A),
		Input::InputHandler::Instance().getKeyBoardState(SDL_SCANCODE_D)
		);
	camera->mouseMove(
		Input::InputHandler::Instance().getMouseRelX(),
		Input::InputHandler::Instance().getMouseRelY());
}