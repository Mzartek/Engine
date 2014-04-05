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
  _lightSpotDirection[0] = 1.0;
  _lightSpotDirection[1] = 0;
  _lightSpotDirection[2] = 0;
  _lightSpotCutOff[0] = 180;
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
  _lightSpotDirection[0] = 1.0;
  _lightSpotDirection[1] = 0;
  _lightSpotDirection[2] = 0;
  _lightSpotCutOff[0] = 180;
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
  _lightSpotDirection[0] = x;
  _lightSpotDirection[1] = y;
  _lightSpotDirection[2] = z;
}

void engine::Light::setCone(const float &x)
{
  _lightSpotCutOff[0] = x;
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

void engine::Light::position(void)
{
  GLfloat target[] = {_lightPosition[0] + _lightSpotDirection[0],
		      _lightPosition[1] + _lightSpotDirection[1],
		      _lightPosition[2] + _lightSpotDirection[2]};
  GLfloat head[] = {0.0, 1.0, 0.0};

  if(_context == NULL)
    {
      std::cerr << "You need to set the GLcontext before" << std::endl;
      return;
    }
  
  matrixLoadIdentity(_viewMatrix);
  matrixLookAt(_viewMatrix, _lightPosition, target, head);
  
  glUseProgram(_context->getProgramId());
  glUniformMatrix4fv(_context->depthViewMatrixLocation, 1, GL_FALSE, _viewMatrix);
  glUniform3fv(_context->lightPositionLocation,  1, _lightPosition);
  glUniform3fv(_context->lightSpotDirectionLocation,  1, _lightSpotDirection);
  glUniform1fv(_context->lightSpotCutOffLocation,  1, _lightSpotCutOff);
  glUniform4fv(_context->lightAmbientLocation,  1, _lightAmbient);
  glUniform4fv(_context->lightDiffuseLocation,  1, _lightDiffuse);
  glUniform4fv(_context->lightSpecularLocation,  1, _lightSpecular);
  glUseProgram(0);

  if(_shadow != NULL)
    {
      glUseProgram(_shadow->getProgramId());
      glUniformMatrix4fv(_shadow->viewMatrixLocation, 1, GL_FALSE, _viewMatrix);
      glUseProgram(0);
    }
}
