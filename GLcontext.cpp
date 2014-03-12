#include <Engine/GLcontext.hpp>

engine::GLcontext::GLcontext(void)
{
  _matrixProgram = NULL;
  _projectionMatrixLocation = -1;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::setProjectionMatrixLocation(ShaderProgram *program, char const *name)
{
  _matrixProgram = program;
  _projectionMatrixLocation = glGetUniformLocation(_matrixProgram->getId(), name);
}

void engine::GLcontext::adjust(int const &w, int const &h, float const &fov, float const &near, float const &far)
{
  glViewport(0, 0, w, h);
  _projectionMatrix = glm::perspective(fov, (float)w / h, near, far);
  _matrixProgram->use();
  glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, &_projectionMatrix[0][0]);
}
