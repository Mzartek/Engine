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
  // GLfloat camera[] = {0, 1, -1};
  // GLfloat target[] = {0, 0, 0};
  GLfloat head[] = {0, 1.0, 0.0};
  
  // matrixOrtho(_projectionMatrix, -100, 100, -100, 100, -100, 100);
  matrixPerspective(_projectionMatrix, fov, (float)GLcontext::width / GLcontext::height, GLcontext::near, GLcontext::far);
  matrixLoadIdentity(_viewMatrix);
  matrixLookAt(_viewMatrix, camera, target, head);
      
  glUseProgram(_context->getProgramId());
  glUniformMatrix4fv(_context->projectionMatrixLocation, 1, GL_FALSE, _projectionMatrix);
  glUniformMatrix4fv(_context->viewMatrixLocation, 1, GL_FALSE, _viewMatrix);
  glUniform3fv(_context->camPositionLocation, 1, camera);
  glUseProgram(0);
}
