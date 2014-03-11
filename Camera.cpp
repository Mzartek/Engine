#include "include/Engine/Camera.hpp"

engine::Camera::Camera(void)
{
  _pcamera._x = 0;
  _pcamera._y = 0;
  _pcamera._z = 0;
  _atheta = _aphi = 0;
  _speed = 1;
}

engine::Camera::Camera(double x, double y, double z)
{ 
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
  _atheta = _aphi = 0;
  _speed = 1;
}

engine::Camera::~Camera(void)
{
}

void engine::Camera::setPosition(double const &x, double const &y, double const &z)
{
  _pcamera._x = x;
  _pcamera._y = y;
  _pcamera._z = z;
}

void engine::Camera::setSpeed(double const &v)
{
  _speed = v;
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
  
  double r_temp = cos(_aphi*M_PI/180);
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

engine::Vecteur<double> engine::Camera::getCamera(void) const
{
  return _pcamera;
}

engine::Vecteur<double> engine::Camera::getTarget(void) const
{
  return _ptarget;
}

engine::Vecteur<double> engine::Camera::getForward(void) const
{
  return _vforward;
}
