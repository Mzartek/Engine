#include <Engine/Input.hpp>

Engine::Input::Input(void)
{
}

Engine::Input::~Input(void)
{
}

GLboolean Engine::Input::getKeyBoardState(const GLubyte &button)
{
	return _keyState[button];
}

GLboolean Engine::Input::getMouseState(const GLubyte &button)
{
	if (_mouseState.buttons & button)
		return GL_TRUE;
	return GL_FALSE;
}

GLint Engine::Input::getMouseRelX(void)
{
	return _mouseState.x;
}

GLint Engine::Input::getMouseRelY(void)
{
	return _mouseState.y;
}

void Engine::Input::refresh(void)
{
	_keyState = SDL_GetKeyboardState(NULL);
	_mouseState.buttons = (GLuint)SDL_GetRelativeMouseState(&_mouseState.x, &_mouseState.y);
}