#ifndef FREE_CAM
#define FREE_CAM

#include "MovableCamera.hpp"

namespace engine
{
  class FreeCam : public MovableCamera
  {
  public:
    FreeCam(void);
    ~FreeCam(void);
    void keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r);
  };
}

#endif
