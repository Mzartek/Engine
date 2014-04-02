#include <Engine/GLcontext.hpp>

engine::GLcontext::GLcontext(void)
{
  _program = NULL;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  projectionMatrixLocation = glGetUniformLocation(_program->getId(), "projectionMatrix");
  viewMatrixLocation = glGetUniformLocation(_program->getId(), "viewMatrix");
  modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
  matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
  matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
  matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
  matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
  camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
  lightPositionLocation = glGetUniformLocation(_program->getId(), "lightPosition");
  lightSpotDirectionLocation = glGetUniformLocation(_program->getId(), "lightSpotDirection");
  lightSpotCutOffLocation = glGetUniformLocation(_program->getId(), "lightSpotCutOff");
  lightAmbientLocation = glGetUniformLocation(_program->getId(), "lightAmbient");
  lightDiffuseLocation = glGetUniformLocation(_program->getId(), "lightDiffuse");
  lightSpecularLocation = glGetUniformLocation(_program->getId(), "lightSpecular");
  textureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
  shadowTextureLocation = glGetUniformLocation(_program->getId(), "shadowTexture");
}

GLuint engine::GLcontext::getProgramId(void)
{
  return _program->getId();
}

void engine::GLcontext::adjust(const int &w, const int &h, const float &fov, const float &near, const float &far)
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glViewport(0, 0, w, h);
  
  matrixPerspective(_projectionMatrix, fov, (float)w / h, near, far);
  glUseProgram(_program->getId());
  glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, _projectionMatrix);
  glUseProgram(0);
}
