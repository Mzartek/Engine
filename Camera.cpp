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

void engine::Camera::setGLcontext(GLcontext *context)
{
  _context = context;
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

void engine::Camera::position(const GLfloat &fov)
{
  GLfloat camera[] = {_pcamera._x, _pcamera._y, _pcamera._z};
  GLfloat target[] = {_ptarget._x, _ptarget._y, _ptarget._z};
  // GLfloat target[] = {0, 0, -10};
  // GLfloat camera[] = {target[0] - 0, target[1]+1, target[2]-0.5f};
  GLfloat head[] = {0, 1.0, 0.0};
  GLfloat camMatrix[16];

  // (void)fov;
  // matrixOrtho(_projectionMatrix, -100, 100, -100, 100, -100, 100);
  matrixPerspective(_projectionMatrix, fov, (float)GLcontext::width / GLcontext::height, GLcontext::near, GLcontext::far);
  matrixLoadIdentity(_viewMatrix);
  matrixLookAt(_viewMatrix, camera, target, head);

  MultiplyMatrices4by4OpenGL_FLOAT(camMatrix, _projectionMatrix, _viewMatrix);
  glUseProgram(_context->getProgramId());
  glUniformMatrix4fv(_context->camMatrixLocation, 1, GL_FALSE, camMatrix);
  glUniform3fv(_context->camPositionLocation, 1, camera);
  glUseProgram(0);
}
