#include "include/Engine/PlayerCam.hpp"

void engine::PlayerCam::keyboardMove(bool const &f, bool const &b, bool const &l, bool const &r)
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
