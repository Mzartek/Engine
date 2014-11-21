#include <Engine/ShadowMap.hpp>

Engine::ShadowMap::ShadowMap(void)
{
}

Engine::ShadowMap::~ShadowMap(void)
{
	if (glIsTexture(_idDepthTexture)) glDeleteTextures(1, &_idDepthTexture);
}

void Engine::ShadowMap::config(const GLuint &width, const GLuint &height)
{
	FrameBuffer::config(width, height);

	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };

	if (glIsTexture(_idDepthTexture)) glDeleteTextures(1, &_idDepthTexture);
	glGenTextures(1, &_idDepthTexture);

	// Frame Buffer Object"
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);

	// Depth Texture
	glBindTexture(GL_TEXTURE_2D, _idDepthTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, _width, _height);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _idDepthTexture, 0);

	glDrawBuffer(GL_NONE);

	if(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;
}

GLuint Engine::ShadowMap::getIdDepthTexture(void) const
{
	return _idDepthTexture;
}

void Engine::ShadowMap::setState(void) const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glDisable(GL_STENCIL_TEST);

	glDisable(GL_BLEND);

	glDisable(GL_CULL_FACE);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void Engine::ShadowMap::clear(void) const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);

	glClearDepth(1.0);

	glDepthMask(GL_TRUE);

	glClear(GL_DEPTH_BUFFER_BIT);
}
