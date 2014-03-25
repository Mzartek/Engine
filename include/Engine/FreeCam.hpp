#ifndef FREE_CAM
#define FREE_CAM

#include "Camera.hpp"

namespace engine
{
  class FreeCam : public Camera
  {
  public:
    void keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r);
  };
}

#endif
