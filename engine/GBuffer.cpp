#include <Engine/GBuffer.hpp>

engine::GBuffer::GBuffer(void)
{
	memset(_idTexture, 0, sizeof _idTexture);
	_idDepthTexture = 0;
}

engine::GBuffer::~GBuffer(void)
{
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(2, _idTexture);
	if(glIsTexture(_idDepthTexture))
		glDeleteTextures(1, &_idDepthTexture);
}

void engine::GBuffer::config(const GLuint &width, const GLuint &height, ShaderProgram *program)
{
	GLuint i;
	GLenum colorAttachment[] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
	};
	
	_width = width;
	_height = height;
  
	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_textureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
	
	// Frame Buffer Object
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);

	// Diffuse and Normal Texture
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(2, _idTexture);
	glGenTextures(2, _idTexture);
	for(i=0 ; i<2 ; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _idTexture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, _width, _height, 0, GL_RGB, GL_FLOAT, 0);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, colorAttachment[i], GL_TEXTURE_2D, _idTexture[i], 0);
	}

	// Depth Texture
	if(glIsTexture(_idDepthTexture))
		glDeleteTextures(1, &_idDepthTexture);
	glGenTextures(1, &_idDepthTexture);
	glBindTexture(GL_TEXTURE_2D, _idDepthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _idDepthTexture, 0);
        
	glDrawBuffers(2, colorAttachment);
    
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLuint engine::GBuffer::getIdTexture(GLuint num) const
{
	if(num>=2)
	{
		std::cerr << "Bad num of texture" << std::endl;
		return 0;
	}
	return _idTexture[num];
}

GLuint engine::GBuffer::getIdDepthTexture(void) const
{
	return _idDepthTexture;
}

GLint engine::GBuffer::getMVPLocation(void) const
{
	return _MVPLocation;
}

GLint engine::GBuffer::getTextureLocation(void) const
{
	return _textureLocation;
}
