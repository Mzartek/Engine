#include <Engine/MovableCamera.hpp>

engine::MovableCamera::MovableCamera(void)
{
  _atheta = _aphi = 0;
  _speed = 1;
}

engine::MovableCamera::~MovableCamera(void)
{
}

void engine::MovableCamera::setSpeed(const float &v)
{
  _speed = v;
}

void engine::MovableCamera::mouseMove(const int &xrel, const int &yrel)
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
  
  _ptarget = _pcamera + _vforward;
}

engine::Vector3D<float> engine::MovableCamera::getForward(void) const
{
  return _vforward;
}
