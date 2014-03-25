#include <Engine/GLcontext.hpp>

engine::GLcontext::GLcontext(void)
{
  _program = NULL;
  _projectionMatrixLocation = -1;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::setProjectionMatrixLocation(ShaderProgram *program, const std::string name)
{
  _program = program;
  _projectionMatrixLocation = glGetUniformLocation(_program->getId(), &name[0]);
}

void engine::GLcontext::adjust(const int &w, const int &h, const float &fov, const float &near, const float &far)
{
  glViewport(0, 0, w, h);
  _projectionMatrix = glm::perspective(fov, (float)w / h, near, far);
  _program->use();
  glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, &_projectionMatrix[0][0]);
}
