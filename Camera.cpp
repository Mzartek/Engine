#include <Engine/Camera.hpp>

engine::Camera::Camera(void)
{
  _pcamera._x = 0;
  _pcamera._y = 0;
  _pcamera._z = 0;
}

engine::Camera::Camera(const float &x, const float &y, const float &z)
{
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
}

engine::Camera::~Camera(void)
{
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

void engine::Camera::setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &near, const GLfloat &far)
{
  _width = width;
  _height = height;
  matrixPerspective(_projectionMatrix, fov, (float)_width / _height, near, far);
}

engine::Vector3D<float> engine::Camera::getPositionCamera(void) const
{
  return _pcamera;
}

engine::Vector3D<float> engine::Camera::getPositionTarget(void) const
{
  return _ptarget;
}

GLuint engine::Camera::getWidth(void) const
{
  return _width;
}

GLuint engine::Camera::getHeight(void) const
{
  return _height;
}

GLfloat *engine::Camera::getMatrix(void)
{
  return _VP;
}

void engine::Camera::position(void)
{
  GLfloat camera[] = {_pcamera._x, _pcamera._y, _pcamera._z};
  GLfloat target[] = {_ptarget._x, _ptarget._y, _ptarget._z};
  GLfloat head[] = {0, 1.0, 0.0};
  GLfloat view[16];

  matrixLoadIdentity(view);
  matrixLookAt(view, camera, target, head);
  MultiplyMatrices4by4OpenGL_FLOAT(_VP, _projectionMatrix, view);
}
