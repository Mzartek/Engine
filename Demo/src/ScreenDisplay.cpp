#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay(void)
{
	_backgroundProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/background/backgroundVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/background/backgroundFrag.glsl");

	_screenProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/screen/screenVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/screen/screenFrag.glsl");

	_screen = new Engine::Screen(_backgroundProgram, _screenProgram);
}

ScreenDisplay::~ScreenDisplay(void)
{
	delete _backgroundProgram;
	delete _screenProgram;
	delete _screen;
}

Engine::Screen *ScreenDisplay::getScreen(void) const
{
	return _screen;
}