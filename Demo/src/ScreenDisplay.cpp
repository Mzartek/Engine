#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay(void)
{
	_backgroundProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/background/backgroundVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/background/backgroundFrag.glsl"));

	_gbuffer = std::shared_ptr<Graphics::GBuffer>(new Graphics::GBuffer(_backgroundProgram));
	_gbuffer->config(
		Graphics::GraphicsRenderer::Instance().getWidth(),
		Graphics::GraphicsRenderer::Instance().getHeight());
}

ScreenDisplay::~ScreenDisplay(void)
{
}

const std::shared_ptr<Graphics::GBuffer> &ScreenDisplay::getGBuffer(void) const
{
	return _gbuffer;
}