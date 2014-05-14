#ifndef MOVABLE_CAMERA
#define MOVABLE_CAMERA

#include "Camera.hpp"

namespace engine
{
  class DLLAPI MovableCamera : public Camera
  {
  private:
    GLfloat _atheta;
    GLfloat _aphi;
  protected:
    Vector3D<GLfloat> *_vforward;
    Vector3D<GLfloat> *_vleft;
    GLfloat _speed;
  public:
    MovableCamera(void);
    ~MovableCamera(void);
    void setSpeed(const GLfloat &v);
    void mouseMove(const GLint &xrel, const GLint &yrel);
    Vector3D<GLfloat> *getForward(void) const;
    virtual void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r) = 0;
  };
}

#endif
