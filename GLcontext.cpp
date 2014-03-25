#include <Engine/GLcontext.hpp>

engine::GLcontext::GLcontext(void)
{
  _program = NULL;
  _projectionMatrixLocation = -1;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  _projectionMatrixLocation = glGetUniformLocation(_program->getId(), "projectionMatrix");
}

void engine::GLcontext::adjust(const int &w, const int &h, const float &fov, const float &near, const float &far)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, w, h);
  
  _projectionMatrix = glm::perspective(fov, (float)w / h, near, far);
  _program->use();
  glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, &_projectionMatrix[0][0]);
}
