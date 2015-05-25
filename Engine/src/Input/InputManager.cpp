#include <Engine/Input/InputManager.hpp>

Engine::Input::InputManager &Engine::Input::InputManager::Instance(void)
{
	static InputManager instance;
	return instance;
}

Engine::Input::InputManager::InputManager(void)
{
}

Engine::Input::InputManager::~InputManager(void)
{
}

GLboolean Engine::Input::InputManager::getKeyBoardState(GLubyte button) const
{
	return _keyState[button];
}

GLboolean Engine::Input::InputManager::getMouseState(GLubyte button) const
{
	if (_mouseState.buttons & button)
		return GL_TRUE;
	return GL_FALSE;
}

GLint Engine::Input::InputManager::getMouseRelX(void) const
{
	return _mouseState.x;
}

GLint Engine::Input::InputManager::getMouseRelY(void) const
{
	return _mouseState.y;
}

void Engine::Input::InputManager::refresh(void)
{
	_keyState = SDL_GetKeyboardState(NULL);
	_mouseState.buttons = (GLuint)SDL_GetRelativeMouseState(&_mouseState.x, &_mouseState.y);
}