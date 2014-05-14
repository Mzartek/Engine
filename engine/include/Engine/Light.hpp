#ifndef LIGHT
#define LIGHT

#include "ShadowMap.hpp"

namespace engine
{
  class DLLAPI Light
  {
  protected:
    ShadowMap *_shadow;
    GLfloat _lightPosition[3];
    GLfloat _lightDirection[3];
    GLfloat _lightAmbient[4];
    GLfloat _lightDiffuse[4];
    GLfloat _lightSpecular[4];
    GLfloat _VP[16];
  public:
    Light(void);
    Light(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    ~Light(void);
    void configShadowMap(const GLuint &width, const GLuint &height, ShaderProgram *program);
    void setPosition(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void setDirection(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    ShadowMap *getShadowMap(void);
    GLfloat *getPosition(void);
    GLfloat *getDirection(void);
    GLfloat *getAmbient(void);
    GLfloat *getDiffuse(void);
    GLfloat *getSpecular(void);
    virtual void position(void) = 0;
    GLfloat *getMatrix(void);
    void newLoop(void) const;
  };
}

#endif
