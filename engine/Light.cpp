#include <Engine/Light.hpp>

engine::Light::Light(void)
{
  GLuint i;
  _lightPosition[0] = 0;
  _lightPosition[1] = 0;
  _lightPosition[2] = 0;
  for(i=0 ; i<4 ; i++)
    {
      _lightAmbient[i]=1.0;
      _lightDiffuse[i]=1.0;
      _lightSpecular[i]=1.0;
    }
  _lightDirection[0] = 1.0;
  _lightDirection[1] = 0;
  _lightDirection[2] = 0;
  _shadow = NULL;
}

engine::Light::Light(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  GLuint i;
  _lightPosition[0] = x;
  _lightPosition[1] = y;
  _lightPosition[2] = z;
  for(i=0 ; i<4 ; i++)
    {
      _lightAmbient[i]=1.0;
      _lightDiffuse[i]=1.0;
      _lightSpecular[i]=1.0;
    }
  _lightDirection[0] = 1.0;
  _lightDirection[1] = 0;
  _lightDirection[2] = 0;
  _shadow = NULL;
}

engine::Light::~Light(void)
{
  if(_shadow!=NULL)
    delete _shadow;
}

void engine::Light::configShadowMap(const GLuint &width, const GLuint &height, ShaderProgram *program)
{
  if(_shadow!=NULL)
    delete _shadow;
  _shadow = new ShadowMap();
  _shadow->config(width, height, program);
}

void engine::Light::setPosition(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  _lightPosition[0] = x;
  _lightPosition[1] = y;
  _lightPosition[2] = z;
}

void engine::Light::setDirection(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  _lightDirection[0] = x;
  _lightDirection[1] = y;
  _lightDirection[2] = z;
}

void engine::Light::setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _lightAmbient[0] = x;
  _lightAmbient[1] = y;
  _lightAmbient[2] = z;
  _lightAmbient[3] = w;
}

void engine::Light::setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _lightDiffuse[0] = x;
  _lightDiffuse[1] = y;
  _lightDiffuse[2] = z;
  _lightDiffuse[3] = w;
}

void engine::Light::setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _lightSpecular[0] = x;
  _lightSpecular[1] = y;
  _lightSpecular[2] = z;
  _lightSpecular[3] = w;
}

engine::ShadowMap *engine::Light::getShadowMap(void)
{
  return _shadow;
}

GLfloat *engine::Light::getPosition(void)
{
  return _lightPosition;
}

GLfloat *engine::Light::getDirection(void)
{
  return _lightDirection;
}

GLfloat *engine::Light::getAmbient(void)
{
  return _lightAmbient;
}

GLfloat *engine::Light::getDiffuse(void)
{
  return _lightDiffuse;
}

GLfloat *engine::Light::getSpecular(void)
{
  return _lightSpecular;
}

GLfloat *engine::Light::getMatrix(void)
{
  return _VP;
}

void engine::Light::newLoop(void) const
{
  if(_shadow==NULL)
    {
      std::cerr << "No need a newLoop for the light when you don't use shadowMapping" << std::endl;
      return;
    }
  _shadow->clear();
}
