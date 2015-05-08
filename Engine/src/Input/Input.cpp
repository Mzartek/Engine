#include <Engine/Input/Input.hpp>

Engine::Input Engine::Input::_instance = Input();

Engine::Input &Engine::Input::Instance(void)
{
	return _instance;
}

Engine::Input::Input(void)
{
}

Engine::Input::~Input(void)
{
}

void Engine::Input::init(void)
{
	this->refresh();
}

GLboolean Engine::Input::getKeyBoardState(GLubyte button) const
{
	return _keyState[button];
}

GLboolean Engine::Input::getMouseState(GLubyte button) const
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