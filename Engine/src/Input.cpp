#include <Engine/Input.hpp>

Engine::Input::Input(void)
{
}

Engine::Input::~Input(void)
{
}

GLboolean Engine::Input::getKeyBoardState(const GLubyte &button) const
{
	return _keyState[button];
}

GLboolean Engine::Input::getMouseState(const GLubyte &button) const
{
	if (_mouseState.buttons & button)
		return GL_TRUE;
	return GL_FALSE;
}

GLint Engine::Input::getMouseRelX(void) const
{
	return _mouseState.x;
}

GLint Engine::Input::getMouseRelY(void) const
{
	return _mouseState.y;
}

void Engine::Input::refresh(void)
{
	_keyState = SDL_GetKeyboardState(NULL);
	_mouseState.buttons = (GLuint)SDL_GetRelativeMouseState(&_mouseState.x, &_mouseState.y);
}