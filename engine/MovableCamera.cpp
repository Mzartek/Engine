#include <Engine/MovableCamera.hpp>

engine::MovableCamera::MovableCamera(void)
{
  _atheta = _aphi = 0;
  _vforward = new Vector3D<GLfloat>;
  _vleft = new Vector3D<GLfloat>;
  _speed = 1;
}

engine::MovableCamera::~MovableCamera(void)
{
  delete _vforward;
  delete _vleft;
}

void engine::MovableCamera::setSpeed(const GLfloat &v)
{
  _speed = v;
}

void engine::MovableCamera::mouseMove(const GLint &xrel, const GLint &yrel)
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
  
  GLfloat r_temp = (GLfloat)cos(_aphi*M_PI/180);
  _vforward->_y = (GLfloat)sin(_aphi*M_PI/180);
  _vforward->_z = r_temp*(GLfloat)cos(_atheta*M_PI / 180);
  _vforward->_x = r_temp*(GLfloat)sin(_atheta*M_PI / 180);

  _vleft->_x = 1*_vforward->_z;
  _vleft->_z = -(1*_vforward->_x);
  *_vleft /= sqrt(_vleft->_x*_vleft->_x + _vleft->_y*_vleft->_y + _vleft->_z*_vleft->_z);
  
  *_ptarget = *_pcamera + *_vforward;
}

engine::Vector3D<GLfloat> *engine::MovableCamera::getForward(void) const
{
  return _vforward;
}
