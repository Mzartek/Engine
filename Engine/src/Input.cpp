#include <Engine/Input.hpp>

engine::Input::Input(void)
{
}

engine::Input::~Input(void)
{
}

GLboolean engine::Input::getKeyBoardState(const GLubyte &button)
{
	return _keyState[button];
}

GLboolean engine::Input::getMouseState(const GLubyte &button)
{
	if (_mouseState.buttons & button)
		return GL_TRUE;
	return GL_FALSE;
}

GLint engine::Input::getMouseRelX(void)
{
	return _mouseState.x;
}

GLint engine::Input::getMouseRelY(void)
{
	return _mouseState.y;
}

void engine::Input::refresh(void)
{
	_keyState = SDL_GetKeyboardState(NULL);
	_mouseState.buttons = (GLuint)SDL_GetRelativeMouseState(&_mouseState.x, &_mouseState.y);
}