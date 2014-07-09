#include <Engine/LBuffer.hpp>

engine::LBuffer::LBuffer(void)
{
	memset(&_idTexture, 0, sizeof _idTexture);
}

engine::LBuffer::~LBuffer(void)
{
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
}

void engine::LBuffer::config(const GLuint &width, const GLuint &height)
{
	GLenum colorAttachment = GL_COLOR_ATTACHMENT0;
	
	_width = width;
	_height = height;
	
	// Frame Buffer Object
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	// Texture
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);

	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32UI, _width, _height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachment, GL_TEXTURE_2D, _idTexture, 0);

	glDrawBuffers(1, &colorAttachment);
    
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint engine::LBuffer::getIdTexture(void) const
{
	return _idTexture;
}

void engine::LBuffer::display(Window *w) const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _idFBO);

	glReadBuffer(GL_COLOR_ATTACHMENT0);

	glBlitFramebuffer(0, 0, _width, _height, 0, 0, w->getWidth(), w->getHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}