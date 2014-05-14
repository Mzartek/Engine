#include <Engine/PlayerCam.hpp>

engine::PlayerCam::PlayerCam(void)
{
  _pcamera = new Vector3D<GLfloat>;
  _ptarget = new Vector3D<GLfloat>;
}

engine::PlayerCam::~PlayerCam(void)
{
  delete _pcamera;
  delete _ptarget;
}

void engine::PlayerCam::keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r)
{
  if(f)
    {
      _pcamera->_x -= _vleft->_z * _speed;
      _pcamera->_z += _vleft->_x * _speed;
    }
  if(b)
    {
      _pcamera->_x += _vleft->_z * _speed;
      _pcamera->_z -= _vleft->_x * _speed;
    }
  if(l)
    *_pcamera += *_vleft * _speed;
  if(r)
    *_pcamera -= *_vleft * _speed;
  
  *_ptarget = *_pcamera + *_vforward;
}
