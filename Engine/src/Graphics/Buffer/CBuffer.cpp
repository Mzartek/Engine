#include <Engine/Graphics/Buffer/CBuffer.hpp>

Engine::Graphics::CBuffer::CBuffer(void)
	: _idTexture(0)
{
}

Engine::Graphics::CBuffer::~CBuffer(void)
{
	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
}

void Engine::Graphics::CBuffer::config(GLuint width, GLuint height)
{
	FrameBuffer::config(width, height);

	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);

	// Frame Buffer Object
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	// Background Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, _width, _height);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _idTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;
}

GLuint Engine::Graphics::CBuffer::getIdTexture(void) const
{
	return _idTexture;
}

void Engine::Graphics::CBuffer::setNormalState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);
	
	glDisable(GL_BLEND);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::Graphics::CBuffer::setAdditiveState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glBlendEquation(GL_FUNC_ADD);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::Graphics::CBuffer::setTransparentState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::Graphics::CBuffer::clear(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glClear(GL_COLOR_BUFFER_BIT);
}
