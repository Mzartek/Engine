#ifndef PLAYER_CAM
#define PLAYER_CAM

#include "Camera.hpp"

namespace engine
{
  class PlayerCam : public Camera
  {
  public:
    void keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r);
  };
}

#endif
