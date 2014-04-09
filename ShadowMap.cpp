#include <Engine/ShadowMap.hpp>

engine::ShadowMap::ShadowMap(void)
{
  _idFBO = 0;
  _idDepthTexture = 0;
  _program = NULL;
}

engine::ShadowMap::~ShadowMap(void)
{
  if(glIsFramebuffer(_idFBO))
    glDeleteFramebuffers(1, &_idFBO);
  if(glIsTexture(_idDepthTexture))
    glDeleteTextures(1, &_idDepthTexture);
}

void engine::ShadowMap::config(const GLuint &width, const GLuint &height, ShaderProgram *program)
{
  _width = width;
  _height = height;
  
  _program = program;
  MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
  
  // Depth Texture for Shadow Mapping
  if(glIsTexture(_idDepthTexture))
    glDeleteTextures(1, &_idDepthTexture);
  glGenTextures(1, &_idDepthTexture);
  glBindTexture(GL_TEXTURE_2D, _idDepthTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Frame Buffer Object
  if(glIsFramebuffer(_idFBO))
    glDeleteFramebuffers(1, &_idFBO);
  glGenFramebuffers(1, &_idFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _idDepthTexture, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer not complete" << std::endl;

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint engine::ShadowMap::getIdFBO(void)
{
  return _idFBO;
}

GLuint engine::ShadowMap::getIdDepthTexture(void)
{
  return _idDepthTexture;
}

GLuint engine::ShadowMap::getProgramId(void)
{
  return _program->getId();
}

void engine::ShadowMap::clear(void)
{
  glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);
  glClear(GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, _width, _height);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
