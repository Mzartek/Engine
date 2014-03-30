#ifndef LIGHT
#define LIGHT

#include "ShaderProgram.hpp"
#include "Vector3D.hpp"

namespace engine
{
  class Light
  {
  protected:
    GLfloat _lightPosition[3];
    GLfloat _lightSpotDirection[3];
    GLfloat _lightSpotCutOff[1];
    GLfloat _lightAmbient[4];
    GLfloat _lightDiffuse[4];
    GLfloat _lightSpecular[4];
    ShaderProgram *_program;
    GLint _lightPositionLocation;
    GLint _lightSpotDirectionLocation;
    GLint _lightSpotCutOffLocation;
    GLint _lightAmbientLocation;
    GLint _lightDiffuseLocation;
    GLint _lightSpecularLocation;
  public:
    Light(void);
    Light(const float &x, const float &y, const float &z);
    ~Light(void);
    void setShaderProgram(ShaderProgram *program);
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
