#include <Engine/PlayerCam.hpp>

void engine::PlayerCam::keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r)
{
  if(f){
    _pcamera._x -= _vleft._z * _speed;
    _pcamera._z += _vleft._x * _speed;
  }
  if(b){
    _pcamera._x += _vleft._z * _speed;
    _pcamera._z -= _vleft._x * _speed;
  }
  if(l)
    _pcamera += _vleft * _speed;
  if(r)
    _pcamera -= _vleft * _speed;
}
