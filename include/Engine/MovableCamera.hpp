#ifndef MOVABLE_CAMERA
#define MOVABLE_CAMERA

#include "Camera.hpp"

namespace engine
{
  class MovableCamera : public Camera
  {
  private:
    float _atheta;
    float _aphi;
  protected:
    Vector3D<float> _vforward;
    Vector3D<float> _vleft;
    float _speed;
  public:
    MovableCamera(void);
    ~MovableCamera(void);
    void setSpeed(const float &v);
    void mouseMove(const int &xrel, const int &yrel);
    Vector3D<float> getForward(void) const;
    virtual void keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r) = 0;
  };
}

#endif
