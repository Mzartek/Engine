#ifndef PLAYER_CAM
#define PLAYER_CAM

#include "Camera.hpp"

namespace engine
{
  class PlayerCam : public Camera
  {
  public:
    void keyboardMove(bool const &f, bool const &b, bool const &l, bool const &r);
  };
}

#endif
