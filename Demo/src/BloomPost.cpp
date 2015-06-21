#include "BloomPost.hpp"

BloomPost::BloomPost(GLuint width, GLuint height)
{
	for (GLuint i = 0; i < NUM_CBUFFER; i++) _cbuffer[i] = std::shared_ptr<Graphics::CBuffer>(new Graphics::CBuffer);
	
	_copyProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/screen/screenVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/screen/copyFrag.glsl"));

	_brightpassProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/screen/screenVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/screen/brightpassFrag.glsl"));

	_gaussianProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/screen/screenVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/screen/gaussianFrag.glsl"));

	_copyProcessing = std::shared_ptr<Graphics::PostProcessing>(new Graphics::PostProcessing(_copyProgram));
	_brightpassProcessing = std::shared_ptr<Graphics::PostProcessing>(new Graphics::PostProcessing(_brightpassProgram));
	_gaussianProcessing = std::shared_ptr<Graphics::PostProcessing>(new Graphics::PostProcessing(_gaussianProgram));

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

	_copyProcessing->display(_cbuffer[0], gbuf->getIdTexture(Graphics::GBuffer::BACKGROUND_ID));
	_brightpassProcessing->display(_cbuffer[1], gbuf->getIdTexture(Graphics::GBuffer::BACKGROUND_ID));

	_copyProcessing->display(_cbuffer[2], _cbuffer[1]->getIdTexture());
	_copyProcessing->display(_cbuffer[3], _cbuffer[1]->getIdTexture());
	_copyProcessing->display(_cbuffer[4], _cbuffer[1]->getIdTexture());
	_copyProcessing->display(_cbuffer[5], _cbuffer[1]->getIdTexture());

	_gaussianProcessing->display(_cbuffer[6], _cbuffer[2]->getIdTexture());
	_gaussianProcessing->display(_cbuffer[7], _cbuffer[3]->getIdTexture());
	_gaussianProcessing->display(_cbuffer[8], _cbuffer[4]->getIdTexture());
	_gaussianProcessing->display(_cbuffer[9], _cbuffer[5]->getIdTexture());

	_copyProcessing->displayAdditive(_cbuffer[0], _cbuffer[6]->getIdTexture());
	_copyProcessing->displayAdditive(_cbuffer[0], _cbuffer[7]->getIdTexture());
	_copyProcessing->displayAdditive(_cbuffer[0], _cbuffer[8]->getIdTexture());
	_copyProcessing->displayAdditive(_cbuffer[0], _cbuffer[9]->getIdTexture());
}

GLuint BloomPost::getTextureId(void)
{
	return _cbuffer[0]->getIdTexture();
}