#include <Engine/Graphics/GBuffer.hpp>

Engine::GBuffer::GBuffer(void)
{
    memset(_idTexture, 0, sizeof _idTexture);
}

Engine::GBuffer::~GBuffer(void)
{
	if (glIsTexture(_idTexture[0])) glDeleteTextures(GBUF_NUM_TEX, _idTexture);
}

void Engine::GBuffer::config(const GLuint &width, const GLuint &height)
{
	FrameBuffer::config(width, height);

	if (glIsTexture(_idTexture[0])) glDeleteTextures(GBUF_NUM_TEX, _idTexture);
	glGenTextures(GBUF_NUM_TEX, _idTexture);

	// Frame Buffer Object
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	// Normal Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_NORMAL]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16F, _width, _height);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _idTexture[GBUF_NORMAL], 0);

	// Material Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_MATERIAL]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32UI, _width, _height);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _idTexture[GBUF_MATERIAL], 0);

	// Light Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_LIGHT]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16F, _width, _height);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _idTexture[GBUF_LIGHT], 0);

	// Background Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_BACKGROUND]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, _width, _height);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, _idTexture[GBUF_BACKGROUND], 0);

	// Depth Stencil Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_DEPTH_STENCIL]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _width, _height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _idTexture[GBUF_DEPTH_STENCIL], 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;
}

GLuint Engine::GBuffer::getIdTexture(const GLuint &num) const
{
	return _idTexture[num];
}

void Engine::GBuffer::setSkyboxState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT3);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);

	glDisable(GL_BLEND);

	glDisable(GL_CULL_FACE);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::GBuffer::setGeometryState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	const GLenum colorAttachment[]
	{
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
	};
	glDrawBuffers(2, colorAttachment);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	glDisable(GL_BLEND);

	glDisable(GL_CULL_FACE);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::GBuffer::setLightState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT2);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_EQUAL, 1, 0xFF);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glBlendEquation(GL_FUNC_ADD);

	glDisable(GL_CULL_FACE);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::GBuffer::setParticlesState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT3);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFF);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	glDisable(GL_CULL_FACE);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::GBuffer::setBackgroundState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT3);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
	glStencilFunc(GL_EQUAL, 1, 0xFF);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	glDisable(GL_CULL_FACE);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::GBuffer::clear(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	const GLenum colorAttachment[]
	{
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
	};
	glDrawBuffers(4, colorAttachment);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0xFF);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Engine::GBuffer::clearLight(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	glDrawBuffer(GL_COLOR_ATTACHMENT2);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glClear(GL_COLOR_BUFFER_BIT);
}