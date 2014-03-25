#ifndef CAMERA
#define CAMERA

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "Vector3D.hpp"

namespace engine
{
  class Camera
  {
  protected:
    Vector3D<float> _pcamera;
    Vector3D<float> _ptarget;
    Vector3D<float> _vforward;
    Vector3D<float> _vleft;
    float _atheta;
    float _aphi;
    float _speed;
    ShaderProgram *_program;
    GLint _viewMatrixLocation;
    glm::mat4 _viewMatrix;
  public:
    Camera(void);
    Camera(float x, float y, float z);
    ~Camera(void);
    void setPosition(const float &x, const float &y, const float &z);
    void setSpeed(const float &v);
    void setViewMatrixLocation(ShaderProgram *program, const std::string name);
    void mouseMove(const int &xrel, const int &yrel);
    void genTarget(void);
    Vector3D<float> getCamera(void) const;
    Vector3D<float> getTarget(void) const;
    Vector3D<float> getForward(void) const;
    void position(void);
    virtual void keyboardMove(const bool &f, const bool &b, const bool &l, const bool &r) = 0;
  };
}

#endif
