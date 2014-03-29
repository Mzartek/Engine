#include <Engine/Camera.hpp>

engine::Camera::Camera(void)
{
  _pcamera._x = 0;
  _pcamera._y = 0;
  _pcamera._z = 0;
  _program = NULL;
  _viewMatrixLocation = -1;
}

engine::Camera::Camera(const float &x, const float &y, const float &z)
{
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
  _program = NULL;
  _viewMatrixLocation = -1;
}

engine::Camera::~Camera(void)
{
}

void engine::Camera::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  _viewMatrixLocation = glGetUniformLocation(_program->getId(), "viewMatrix");
}

void engine::Camera::setPositionCamera(const float &x, const float &y, const float &z)
{
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
}

void engine::Camera::setPositionTarget(const float &x, const float &y, const float &z)
{
  _ptarget._x = x;
  _ptarget._y = y;
  _ptarget._z = z;
}

engine::Vector3D<float> engine::Camera::getPositionCamera(void) const
{
  return _pcamera;
}

engine::Vector3D<float> engine::Camera::getPositionTarget(void) const
{
  return _ptarget;
}

void engine::Camera::position(void)
{
  GLfloat camera[] = {_pcamera._x, _pcamera._y, _pcamera._z};
  GLfloat target[] = {_ptarget._x, _ptarget._y, _ptarget._z};
  GLfloat head[] = {0.0, 1.0, 0.0};
  matrixLoadIdentity(_viewMatrix);
  matrixLookAt(_viewMatrix, camera, target, head);
      
  _program->use();
  glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, _viewMatrix);
  glUseProgram(0);
}
