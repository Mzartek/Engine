#include <Engine/Light.hpp>

engine::Light::Light(void)
{
  unsigned i;
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
  _context = NULL;
  _shadow = NULL;
}

engine::Light::Light(const float &x, const float &y, const float &z)
{
  unsigned i;
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
  _context = NULL;
  _shadow = NULL;
}

engine::Light::~Light(void)
{
}

void engine::Light::setGLcontext(GLcontext *context)
{
  _context = context;
}

void engine::Light::setShadowMap(ShadowMap *shadow)
{
  _shadow = shadow;
}

void engine::Light::setPosition(const float &x, const float &y, const float &z)
{
  _lightPosition[0] = x;
  _lightPosition[1] = y;
  _lightPosition[2] = z;
}

void engine::Light::setDirection(const float &x, const float &y, const float &z)
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

engine::Vector3D<float> engine::Light::getPosition(void)
{
  engine::Vector3D<float> tmp;
  tmp._x = _lightPosition[0];
  tmp._y = _lightPosition[1];
  tmp._z = _lightPosition[2];
  return tmp;
}
