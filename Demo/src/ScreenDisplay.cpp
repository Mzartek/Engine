#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay(void)
{
	_backgroundProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/background/backgroundVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/background/backgroundFrag.glsl"));

	_screenProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/screen/screenVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/screen/screenFrag.glsl"));

	_screen = std::shared_ptr<Engine::Screen>(new Engine::Screen(_backgroundProgram, _screenProgram));
}

ScreenDisplay::~ScreenDisplay(void)
{
}

const std::shared_ptr<Engine::Screen> &ScreenDisplay::getScreen(void) const
{
	return _screen;
}