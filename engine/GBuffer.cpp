#include <Engine/GBuffer.hpp>

engine::GBuffer::GBuffer(void)
{
	colorAttachment[GBUF_NORMAL] = GL_COLOR_ATTACHMENT0;
	colorAttachment[GBUF_MATERIAL] = GL_COLOR_ATTACHMENT1;
	memset(_idTexture, 0, sizeof _idTexture);
}

engine::GBuffer::~GBuffer(void)
{
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(GBUF_NUM_TEX, _idTexture);
}

void engine::GBuffer::config(const GLuint &width, const GLuint &height)
{
	_width = width;
	_height = height;

	// Frame Buffer GLObject
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	// Texture
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(GBUF_NUM_TEX, _idTexture);
	glGenTextures(GBUF_NUM_TEX, _idTexture);

	// Normal Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_NORMAL]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, _width, _height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachment[GBUF_NORMAL], GL_TEXTURE_2D, _idTexture[GBUF_NORMAL], 0);

	// Material Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_MATERIAL]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32UI, _width, _height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachment[GBUF_MATERIAL], GL_TEXTURE_2D, _idTexture[GBUF_MATERIAL], 0);

	// Depth Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[GBUF_DEPTH]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32, _width, _height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _idTexture[GBUF_DEPTH], 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint engine::GBuffer::getIdTexture(const GLuint &num) const
{
	if (num >= GBUF_NUM_TEX)
	{
		std::cerr << "Bad num of texture" << std::endl;
		return 0;
	}
	return _idTexture[num];
}

void engine::GBuffer::display(Window *w, const GLuint &buf) const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _idFBO);

	glReadBuffer(colorAttachment[buf]);

	glBlitFramebuffer(0, 0, _width, _height, 0, 0, w->getWidth(), w->getHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void engine::GBuffer::clear(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, _width, _height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}