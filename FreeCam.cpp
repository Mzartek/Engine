#include "include/Engine/FreeCam.hpp"

void engine::FreeCam::keyboardMove(bool const &f, bool const &b, bool const &l, bool const &r)
{
  if(f)
    _pcamera += _vforward * _speed;
  if(b)
    _pcamera -= _vforward * _speed;
  if(l)
    _pcamera += _vleft * _speed;
  if(r)
    _pcamera -= _vleft * _speed;
}
