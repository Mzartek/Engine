#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay(const GLchar *title, GLint w, GLint h, GLboolean fullScreen)
{
		_windowProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
				"../share/Demo/shader/window/windowVert.glsl",
				NULL,
				NULL,
				NULL,
				"../share/Demo/shader/window/windowFrag.glsl"));

		_backgroundProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
				"../share/Demo/shader/background/backgroundVert.glsl",
				NULL,
				NULL,
				NULL,
				"../share/Demo/shader/background/backgroundFrag.glsl"));

		_window = std::shared_ptr<Graphics::Window>(new Graphics::Window(title, w, h, fullScreen, _windowProgram));
		_gBuffer = std::shared_ptr<Graphics::GBuffer>(new Graphics::GBuffer(_backgroundProgram));
		_gBuffer->config(w, h);
}

ScreenDisplay::~ScreenDisplay(void)
{
}

const std::shared_ptr<Graphics::Window> &ScreenDisplay::getWindow(void) const
{
		return _window;
}

const std::shared_ptr<Graphics::GBuffer> &ScreenDisplay::getGBuffer(void) const
{
		return _gBuffer;
}