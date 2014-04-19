#ifndef PLAYER_CAM
#define PLAYER_CAM

#include "MovableCamera.hpp"

namespace engine
{
  class PlayerCam : public MovableCamera
  {
  public:
    PlayerCam(void);
    ~PlayerCam(void);
    void keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r);
  };
}

#endif
