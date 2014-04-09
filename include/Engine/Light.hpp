#ifndef LIGHT
#define LIGHT

#include "GLcontext.hpp"
#include "ShadowMap.hpp"
#include "Vector3D.hpp"

namespace engine
{
  class Light
  {
  protected:
    GLcontext *_context;
    ShadowMap *_shadow;
    GLfloat _projectionMatrix[16];
    GLfloat _viewMatrix[16];
    GLfloat _lightPosition[3];
    GLfloat _lightDirection[3];
    GLfloat _lightSpotCutOff[1];
    GLfloat _lightAmbient[4];
    GLfloat _lightDiffuse[4];
    GLfloat _lightSpecular[4];
  public:
    Light(void);
    Light(const float &x, const float &y, const float &z);
    ~Light(void);
    void setGLcontext(GLcontext *context);
    void setShadowMap(ShadowMap *shadow);
    void setPosition(const float &x, const float &y, const float &z);
    void setDirection(const float &x, const float &y, const float &z);
    void setCone(const float &x);
    void setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    Vector3D<float> getPosition(void);
    void position(void);
  };
}

#endif
