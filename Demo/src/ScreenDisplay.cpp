#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay(void)
{
	_backgroundProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/background/backgroundVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/background/backgroundFrag.glsl"));

	_screenProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/screen/screenVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/screen/screenFrag.glsl"));

	_screen = new_ref(Engine::Screen(_backgroundProgram, _screenProgram));
}

ScreenDisplay::~ScreenDisplay(void)
{
	release_ref(_backgroundProgram);
	release_ref(_screenProgram);
	release_ref(_screen);
}

Engine::Screen *ScreenDisplay::getScreen(void) const
{
	return _screen;
}