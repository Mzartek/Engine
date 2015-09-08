#include "BloomPost.hpp"

#include <Engine/Graphics/Screen.hpp>

BloomPost::BloomPost(GLuint width, GLuint height)
{
	for (GLuint i = 0; i < NUM_CBUFFER; i++) _cbuffer[i] = std::make_shared<Graphics::CBuffer>();
	
	_copyProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/screen/screenVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/screen/copyFrag.glsl");

	_brightpassProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/screen/screenVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/screen/brightpassFrag.glsl");

	_gaussianProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/screen/screenVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/screen/gaussianFrag.glsl");

	_cbuffer[0]->config(width, height);
	_cbuffer[1]->config(width, height);

	_cbuffer[2]->config(_cbuffer[1]->getWidth() / 2, _cbuffer[1]->getHeight() / 2);
	_cbuffer[3]->config(_cbuffer[2]->getWidth() / 2, _cbuffer[2]->getHeight() / 2);
	_cbuffer[4]->config(_cbuffer[3]->getWidth() / 2, _cbuffer[3]->getHeight() / 2);
	_cbuffer[5]->config(_cbuffer[4]->getWidth() / 2, _cbuffer[4]->getHeight() / 2);

	_cbuffer[6]->config(_cbuffer[2]->getWidth(), _cbuffer[2]->getHeight());
	_cbuffer[7]->config(_cbuffer[3]->getWidth(), _cbuffer[3]->getHeight());
	_cbuffer[8]->config(_cbuffer[4]->getWidth(), _cbuffer[4]->getHeight());
	_cbuffer[9]->config(_cbuffer[5]->getWidth(), _cbuffer[5]->getHeight());
}

BloomPost::~BloomPost(void)
{
}

void BloomPost::applyFilter(const std::shared_ptr<Graphics::GBuffer> &gbuf)
{
	for (GLuint i = 0; i < NUM_CBUFFER; i++) _cbuffer[i]->clear();

	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[0], gbuf, _copyProgram);
	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[1], gbuf, _brightpassProgram);

	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[2], _cbuffer[1], _copyProgram);
	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[3], _cbuffer[1], _copyProgram);
	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[4], _cbuffer[1], _copyProgram);
	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[5], _cbuffer[1], _copyProgram);

	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[6], _cbuffer[2], _gaussianProgram);
	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[7], _cbuffer[3], _gaussianProgram);
	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[8], _cbuffer[4], _gaussianProgram);
	Graphics::Screen::Instance().displayOnCBuffer(_cbuffer[9], _cbuffer[5], _gaussianProgram);

	Graphics::Screen::Instance().displayOnCBufferAdditive(_cbuffer[0], _cbuffer[6], _copyProgram);
	Graphics::Screen::Instance().displayOnCBufferAdditive(_cbuffer[0], _cbuffer[7], _copyProgram);
	Graphics::Screen::Instance().displayOnCBufferAdditive(_cbuffer[0], _cbuffer[8], _copyProgram);
	Graphics::Screen::Instance().displayOnCBufferAdditive(_cbuffer[0], _cbuffer[9], _copyProgram);
}

const std::shared_ptr<Graphics::CBuffer> &BloomPost::getCBuffer(void)
{
	return _cbuffer[0];
}