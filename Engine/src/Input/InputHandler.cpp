#include <Engine/Input/InputHandler.hpp>

Engine::Input::InputHandler &Engine::Input::InputHandler::Instance(void)
{
	static InputHandler instance;
	return instance;
}

Engine::Input::InputHandler::InputHandler(void)
	: _keyState(nullptr)
{
}

Engine::Input::InputHandler::~InputHandler(void)
{
}

GLboolean Engine::Input::InputHandler::getKeyBoardState(GLubyte button) const
{
	return _keyState[button];
}

GLboolean Engine::Input::InputHandler::getMouseState(GLubyte button) const
{
	if (_mouseState.buttons & button)
		return GL_TRUE;
	return GL_FALSE;
}

GLint Engine::Input::InputHandler::getMouseRelX(void) const
{
	return _mouseState.x;
}

GLint Engine::Input::InputHandler::getMouseRelY(void) const
{
	return _mouseState.y;
}

void Engine::Input::InputHandler::refresh(void)
{
	_keyState = SDL_GetKeyboardState(nullptr);
	_mouseState.buttons = static_cast<GLuint>(SDL_GetRelativeMouseState(&_mouseState.x, &_mouseState.y));
}