#ifndef CAMERA
#define CAMERA

#include "matrix.h"
#include "ShaderProgram.hpp"
#include "Vector3D.hpp"

namespace engine
{
  class Camera
  {
  protected:
    Vector3D<float> _pcamera;
    Vector3D<float> _ptarget;
    ShaderProgram *_program;
    GLint _viewMatrixLocation;
    GLfloat _viewMatrix[16];
  public:
    Camera(void);
    Camera(const float &x, const float &y, const float &z);
    ~Camera(void);
    void setShaderProgram(ShaderProgram *program);
    void setPositionCamera(const float &x, const float &y, const float &z);
    void setPositionTarget(const float &x, const float &y, const float &z);
    Vector3D<float> getPositionCamera(void) const;
    Vector3D<float> getPositionTarget(void) const;
    void position(void);
  };
}

#endif
