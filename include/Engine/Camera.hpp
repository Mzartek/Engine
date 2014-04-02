#ifndef CAMERA
#define CAMERA

#include "matrix.h"
#include "GLcontext.hpp"
#include "Vector3D.hpp"

namespace engine
{
  class Camera
  {
  private:
    GLcontext *_context;
    GLfloat _viewMatrix[16];
  protected:
    Vector3D<GLfloat> _pcamera;
    Vector3D<GLfloat> _ptarget;
  public:
    Camera(void);
    Camera(const float &x, const float &y, const float &z);
    ~Camera(void);
    void setGLcontext(GLcontext *context);
    void setPositionCamera(const float &x, const float &y, const float &z);
    void setPositionTarget(const float &x, const float &y, const float &z);
    Vector3D<float> getPositionCamera(void) const;
    Vector3D<float> getPositionTarget(void) const;
    void position(void);
  };
}

#endif
