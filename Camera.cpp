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
  GLfloat head[] = {0, 1.0, 0.0};
  GLfloat projection[16], view[16];

  if(_context == NULL)
    {
      std::cerr << "You need to set the GLcontext before" << std::endl;
      return;
    }

  matrixPerspective(projection, fov, (float)GLcontext::width / GLcontext::height, GLcontext::near, GLcontext::far);
  matrixLoadIdentity(view);
  matrixLookAt(view, camera, target, head);
  MultiplyMatrices4by4OpenGL_FLOAT(_context->VP, projection, view);

  glUseProgram(_context->getProgramId());
  glUniform3fv(_context->camPositionLocation, 1, camera);
  glUseProgram(0);
}
