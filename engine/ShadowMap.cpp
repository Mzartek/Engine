#include <Engine/ShadowMap.hpp>

engine::ShadowMap::ShadowMap(void)
{
	_idDepthTexture = 0;
	_program = NULL;
}

engine::ShadowMap::~ShadowMap(void)
{
	if(glIsTexture(_idDepthTexture))
		glDeleteTextures(1, &_idDepthTexture);
}

void engine::ShadowMap::config(const GLuint &width, const GLuint &height, ShaderProgram *program)
{
	_width = width;
	_height = height;
  
	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_colorTextureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
	_shadowMapLocation = glGetUniformLocation(_program->getId(), "shadowMap");
	_alphaLocation = glGetUniformLocation(program->getId(), "alpha");
	_screenLocation = glGetUniformLocation(_program->getId(), "screen");

	// Frame Buffer Object"
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
	glGenFramebuffers(1, &_idFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _idFBO);
  
	// Depth Texture
	if(glIsTexture(_idDepthTexture))
		glDeleteTextures(1, &_idDepthTexture);
	glGenTextures(1, &_idDepthTexture);
	glBindTexture(GL_TEXTURE_2D, _idDepthTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32, _width, _height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _idDepthTexture, 0);
	
	glDrawBuffer(GL_NONE);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete" << std::endl;
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLuint engine::ShadowMap::getIdDepthTexture(void) const
{
	return _idDepthTexture;
}

GLuint engine::ShadowMap::getProgramId(void) const
{
	return _program->getId();
}

GLint engine::ShadowMap::getMVPLocation(void) const
{
	return _MVPLocation;
}

GLint engine::ShadowMap::getColorTextureLocation(void) const
{
	return _colorTextureLocation;
}

GLint engine::ShadowMap::getShadowMapLocation(void) const
{
	return _shadowMapLocation;
}

GLint engine::ShadowMap::getScreenLocation(void) const
{
	return _screenLocation;
}

GLint engine::ShadowMap::getAlphaLocation(void) const
{
	return _alphaLocation;
}