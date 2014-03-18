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

void engine::Camera::setPosition(float const &x, float const &y, float const &z)
{
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
}

void engine::Camera::setSpeed(float const &v)
{
  _speed = v;
}

void engine::Camera::setViewMatrixLocation(ShaderProgram *program, char const *name)
{
  _program = program;
  _viewMatrixLocation = glGetUniformLocation(_program->getId(), name);
}

void engine::Camera::mouseMove(int const &xrel, int const &yrel)
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
  _viewMatrix = glm::lookAt(glm::vec3(_pcamera._x, _pcamera._y, _pcamera._z),
			    glm::vec3(_ptarget._x, _ptarget._y, _ptarget._z),
			    glm::vec3(0.0, 1.0, 0.0));
  _program->use();
  glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &_viewMatrix[0][0]);
}
