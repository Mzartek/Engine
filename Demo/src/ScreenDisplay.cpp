#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay(void)
{
	_backgroundProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/background/backgroundVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/background/backgroundFrag.glsl"));

	_screenProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/screen/screenVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/screen/screenFrag.glsl"));

	_screen = new_ptr(Engine::Screen(_backgroundProgram, _screenProgram));
}

ScreenDisplay::~ScreenDisplay(void)
{
	release_ptr(_backgroundProgram);
	release_ptr(_screenProgram);
	release_ptr(_screen);
}

Engine::Screen *ScreenDisplay::getScreen(void) const
{
	return _screen;
}