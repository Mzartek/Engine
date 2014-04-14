#ifndef CAMERA
#define CAMERA

#include "GL.hpp"
#include "matrix.h"
#include "Vector3D.hpp"

namespace engine
{
  class Camera
  {
  protected:
    Vector3D<GLfloat> _pcamera;
    Vector3D<GLfloat> _ptarget;
    GLuint _width;
    GLuint _height;
    GLfloat _projectionMatrix[16];
    GLfloat _VP[16];
  public:
    Camera(void);
    Camera(const float &x, const float &y, const float &z);
    ~Camera(void);
    void setPositionCamera(const float &x, const float &y, const float &z);
    void setPositionTarget(const float &x, const float &y, const float &z);
    void setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &near, const GLfloat &far);
    Vector3D<float> getPositionCamera(void) const;
    Vector3D<float> getPositionTarget(void) const;
    GLuint getWidth(void) const;
    GLuint getHeight(void) const;
    GLfloat *getMatrix(void);
    void position(void);
  };
}

#endif
