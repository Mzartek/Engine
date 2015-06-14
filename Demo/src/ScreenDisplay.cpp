#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay(void)
{
	_backgroundProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/background/backgroundVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/background/backgroundFrag.glsl"));

	_screenProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/window/windowVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/window/windowFrag.glsl"));

	_screen = std::shared_ptr<Graphics::Screen>(new Graphics::Screen(_backgroundProgram, _screenProgram));
}

ScreenDisplay::~ScreenDisplay(void)
{
}

const std::shared_ptr<Graphics::Screen> &ScreenDisplay::getScreen(void) const
{
	return _screen;
}