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
  _projectionMatrixLocation = glGetUniformLocation(_program->getId(), "depthProjectionMatrix");
  _viewMatrixLocation = glGetUniformLocation(_program->getId(), "depthViewMatrix");
  _modelMatrixLocation = glGetUniformLocation(_program->getId(), "depthModelMatrix");
  
  // Depth Texture for Shadow Mapping
  glGenTextures(1, &_idDepthTexture);
  glBindTexture(GL_TEXTURE_2D, _idDepthTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Frame Buffer Object
  glGenFramebuffers(1, &_idFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _idDepthTexture, 0);
  glDrawBuffer(GL_NONE);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer not complete" << std::endl;

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  matrixOrtho(_projectionMatrix, -10, 10, -10, 10, -10, 1200);
  _program->use();
  glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, _projectionMatrix);
  glUseProgram(0);
}

void engine::ShadowMap::drawIn(Light *theLight, Model *theModel)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glViewport(0, 0, _width, _height);

  _program->use();
  glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, theLight->_viewMatrix);
  glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, theModel->_modelMatrix);
  
  glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);

  theModel->display();
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glUseProgram(0);
}
