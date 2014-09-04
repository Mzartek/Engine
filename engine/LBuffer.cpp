#include <Engine/LBuffer.hpp>

engine::LBuffer::LBuffer(void)
{
	_colorAttachment = GL_COLOR_ATTACHMENT0;
	_idTexture = 0;
}

engine::LBuffer::~LBuffer(void)
{
	if (glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
}

void engine::LBuffer::config(const GLuint &width, const GLuint &height)
{
	_width = width;
	_height = height;

	// Frame Buffer GLObject
	if (glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);

	// Texture
	if (glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);

	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, _width, _height);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, _colorAttachment, GL_TEXTURE_2D, _idTexture, 0);

	glDrawBuffers(1, &_colorAttachment);

	if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLuint engine::LBuffer::getIdTexture(void) const
{
	return _idTexture;
}

void engine::LBuffer::clear(void) const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
