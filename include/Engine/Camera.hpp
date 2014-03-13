#ifndef CAMERA
#define CAMERA

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "Vecteur.hpp"

namespace engine
{
  class Camera
  {
  protected:
    Vecteur<float> _pcamera;
    Vecteur<float> _ptarget;
    Vecteur<float> _vforward;
    Vecteur<float> _vleft;
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
    void setPosition(float const &x, float const &y, float const &z);
    void setSpeed(float const &v);
    void setViewMatrixLocation(ShaderProgram *program, char const *name);
    void mouseMove(int const &xrel, int const &yrel);
    void genTarget(void);
    Vecteur<float> getCamera(void) const;
    Vecteur<float> getTarget(void) const;
    Vecteur<float> getForward(void) const;
    void position(void);
    virtual void keyboardMove(bool const &f, bool const &b, bool const &l, bool const &r) = 0;
  };
}

#endif
