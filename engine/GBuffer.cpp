#include <Engine/GBuffer.hpp>

engine::GBuffer::GBuffer(void)
{
	memset(_idTexture, 0, sizeof _idTexture);
	_idDepthRender = 0;
}

engine::GBuffer::~GBuffer(void)
{
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(3, _idTexture);
	if(glIsRenderbuffer(_idDepthRender))
		glDeleteRenderbuffers(1, &_idDepthRender);
}

void engine::GBuffer::config(const GLuint &width, const GLuint &height, ShaderProgram *program)
{
	GLuint i;
	GLenum colorAttachment[] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
	};
	
	_width = width;
	_height = height;
  
	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
	_normalMatrixLocation = glGetUniformLocation(_program->getId(), "normalMatrix");
	_shininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
	
	// Frame Buffer Object
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);

	// Texture
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(3, _idTexture);
	glGenTextures(3, _idTexture);
	for(i=0 ; i<2 ; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _idTexture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, _width, _height, 0, GL_RGB, GL_FLOAT, 0);
		// glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_RGB32F, _width, _height, GL_TRUE);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, colorAttachment[i], GL_TEXTURE_2D, _idTexture[i], 0);
	}

	// Shininess Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, _width, _height, 0, GL_RGB, GL_FLOAT, 0);
	// glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_R32F, _width, _height, GL_TRUE);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, colorAttachment[i], GL_TEXTURE_2D, _idTexture[i], 0);

	// Depth Render
	if(glIsRenderbuffer(_idDepthRender))
		glDeleteRenderbuffers(1, &_idDepthRender);
	glGenRenderbuffers(1, &_idDepthRender);
	glBindRenderbuffer(GL_RENDERBUFFER, _idDepthRender);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _idDepthRender);

	glDrawBuffers(3, colorAttachment);
    
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLuint engine::GBuffer::getIdTexture(GLuint num) const
{
	if(num>=3)
	{
		std::cerr << "Bad num of texture" << std::endl;
		return 0;
	}
	return _idTexture[num];
}

GLuint engine::GBuffer::getIdDepthRender(void) const
{
	return _idDepthRender;
}

GLint engine::GBuffer::getMVPLocation(void) const
{
	return _MVPLocation;
}

GLint engine::GBuffer::getModelMatrixLocation(void) const
{
	return _modelMatrixLocation;
}

GLint engine::GBuffer::getNormalMatrixLocation(void) const
{
	return _normalMatrixLocation;
}

GLint engine::GBuffer::getShininessLocation(void) const
{
	return _shininessLocation;
}
