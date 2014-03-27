#include <Engine/Camera.hpp>

engine::Camera::Camera(void)
{
  _pcamera._x = 0;
  _pcamera._y = 0;
  _pcamera._z = 0;
  _atheta = _aphi = 0;
  _speed = 1;
  _program = NULL;
  _viewMatrixLocation = -1;
}

engine::Camera::Camera(float x, float y, float z)
{ 
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
  _atheta = _aphi = 0;
  _speed = 1;
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

void engine::Camera::setPosition(const float &x, const float &y, const float &z)
{
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
}

void engine::Camera::setSpeed(const float &v)
{
  _speed = v;
}

void engine::Camera::mouseMove(const int &xrel, const int &yrel)
{
  _atheta -= xrel;
  _aphi -= yrel;

  if(_atheta > 360)
    _atheta -= 360;
  else if(_atheta < -360)
    _atheta += 360;
  if (_aphi > 89)
    _aphi = 89;
  else if (_aphi < -89)
    _aphi = -89;
  
  float r_temp = cos(_aphi*M_PI/180);
  _vforward._y = sin(_aphi*M_PI/180);
  _vforward._z = r_temp*cos(_atheta*M_PI/180);
  _vforward._x = r_temp*sin(_atheta*M_PI/180);

  _vleft._x = 1*_vforward._z;
  _vleft._z = -(1*_vforward._x);
  _vleft /= sqrt(_vleft._x*_vleft._x + _vleft._y*_vleft._y + _vleft._z*_vleft._z);
}

void engine::Camera::genTarget(void)
{
  _ptarget = _pcamera + _vforward;
}

engine::Vector3D<float> engine::Camera::getCamera(void) const
{
  return _pcamera;
}

engine::Vector3D<float> engine::Camera::getTarget(void) const
{
  return _ptarget;
}

engine::Vector3D<float> engine::Camera::getForward(void) const
{
  return _vforward;
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
}
