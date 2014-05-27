#include <Engine/LBuffer.hpp>

engine::LBuffer::LBuffer(void)
{
	memset(_idTexture, 0, sizeof _idTexture);
}

engine::LBuffer::~LBuffer(void)
{
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(2, _idTexture);
}

void engine::LBuffer::config(const GLuint &width, const GLuint &height)
{
	GLuint i;
	GLenum colorAttachment[] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
	};
	
	_width = width;
	_height = height;
	
	// Frame Buffer Object
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);

	// Texture
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(2, _idTexture);
	glGenTextures(2, _idTexture);
	for(i=0 ; i<2 ; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _idTexture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, colorAttachment[i], GL_TEXTURE_2D, _idTexture[i], 0);
	}

	glDrawBuffers(2, colorAttachment);
    
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLuint engine::LBuffer::getIdTexture(GLuint num) const
{
	if(num>=2)
	{
		std::cerr << "Bad num of texture" << std::endl;
		return 0;
	}
	return _idTexture[num];
}
