#include <Engine/GBuffer.hpp>

engine::GBuffer::GBuffer(void)
{
	memset(_idTexture, 0, sizeof _idTexture);
	_idDepthRender = 0;
}

engine::GBuffer::~GBuffer(void)
{
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(GBUF_NUM_TEX, _idTexture);
	if(glIsRenderbuffer(_idDepthRender))
		glDeleteRenderbuffers(1, &_idDepthRender);
}

void engine::GBuffer::config(const GLuint &width, const GLuint &height, ShaderProgram *program, GLboolean withColor)
{
	GLenum colorAttachment[] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2
	};
	
	_width = width;
	_height = height;
  
	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
	_normalMatrixLocation = glGetUniformLocation(_program->getId(), "normalMatrix");
	_matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
	_matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
	_matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
	_matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
	_colorTextureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
	_gBufferMaterialTextureLocation = glGetUniformLocation(_program->getId(), "gBufferMaterialTexture");
	
	// Frame Buffer Object
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

	// Texture
	if(glIsTexture(_idTexture[0]))
		glDeleteTextures(GBUF_NUM_TEX, _idTexture);
	glGenTextures(GBUF_NUM_TEX, _idTexture);
	
	// Position Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[0]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, _width, _height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachment[0], GL_TEXTURE_2D, _idTexture[0], 0);
	
	// Normal Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[1]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, _width, _height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachment[1], GL_TEXTURE_2D, _idTexture[1], 0);
	
	// Material Texture
	glBindTexture(GL_TEXTURE_2D, _idTexture[2]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32UI, _width, _height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachment[2], GL_TEXTURE_2D, _idTexture[2], 0);
	
	glDrawBuffers(GBUF_NUM_TEX, colorAttachment);

	if (withColor)
		std::cout << "LOL" << std::endl;

	// Depth Render
	if(glIsRenderbuffer(_idDepthRender))
		glDeleteRenderbuffers(1, &_idDepthRender);
	glGenRenderbuffers(1, &_idDepthRender);
	glBindRenderbuffer(GL_RENDERBUFFER, _idDepthRender);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _idDepthRender);
    
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint engine::GBuffer::getIdTexture(GLuint num) const
{
	if (num >= GBUF_NUM_TEX)
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

GLint engine::GBuffer::getMatAmbientLocation(void) const
{
	return _matAmbientLocation;
}

GLint engine::GBuffer::getMatDiffuseLocation(void) const
{
	return _matDiffuseLocation;
}

GLint engine::GBuffer::getMatSpecularLocation(void) const
{
	return _matSpecularLocation;
}

GLint engine::GBuffer::getMatShininessLocation(void) const
{
	return _matShininessLocation;
}

GLint engine::GBuffer::getColorTextureLocation(void) const
{
	return _colorTextureLocation;
}

GLint engine::GBuffer::getGBufferMaterialTextureLocation(void) const
{
	return _gBufferMaterialTextureLocation;
}

void engine::GBuffer::display(Window *w, GLuint buf) const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _idFBO);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + buf);

	glBlitFramebuffer(0, 0, _width, _height, 0, 0, w->getWidth(), w->getHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}