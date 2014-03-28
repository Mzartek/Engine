#include <Engine/FreeCam.hpp>

void engine::FreeCam::keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r)
{
  if(f)
    _pcamera += _vforward * _speed;
  if(b)
    _pcamera -= _vforward * _speed;
  if(l)
    _pcamera += _vleft * _speed;
  if(r)
    _pcamera -= _vleft * _speed;
  
  _ptarget = _pcamera + _vforward;
}
