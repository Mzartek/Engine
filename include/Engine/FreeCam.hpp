#ifndef FREE_CAM
#define FREE_CAM

#include "Camera.hpp"

namespace engine
{
  class FreeCam : public Camera
  {
  public:
    void keyboardMove(bool const &f, bool const &b, bool const &l, bool const &r);
  };
}

#endif
