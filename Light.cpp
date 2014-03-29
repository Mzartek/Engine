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
  _spotDirection[0] = 1.0;
  _spotDirection[1] = 0;
  _spotDirection[2] = 0;
  _spotCone[0] = 180;
  _program = NULL;
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
  _spotDirection[0] = 1.0;
  _spotDirection[1] = 0;
  _spotDirection[2] = 0;
  _spotCone[0] = 180;
  _program = NULL;
}

engine::Light::~Light(void)
{
}

void engine::Light::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  _lightPositionLocation = glGetUniformLocation(_program->getId(), "lightPosition");
  _spotDirectionLocation = glGetUniformLocation(_program->getId(), "spotDirection");
  _spotConeLocation = glGetUniformLocation(_program->getId(), "spotCone");
  _lightAmbientLocation = glGetUniformLocation(_program->getId(), "lightAmbient");
  _lightDiffuseLocation = glGetUniformLocation(_program->getId(), "lightDiffuse");
  _lightSpecularLocation = glGetUniformLocation(_program->getId(), "lightSpecular");
}

void engine::Light::setPosition(const float &x, const float &y, const float &z)
{
  _lightPosition[0] = x;
  _lightPosition[1] = y;
  _lightPosition[2] = z;
}

void engine::Light::setDirection(const float &x, const float &y, const float &z)
{
  _spotDirection[0] = x;
  _spotDirection[1] = y;
  _spotDirection[2] = z;
}

void engine::Light::setCone(const float &x)
{
  _spotCone[0] = x;
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
  _program->use();
  glUniform3fv(_lightPositionLocation,  1, _lightPosition);
  glUniform3fv(_spotDirectionLocation,  1, _spotDirection);
  glUniform1fv(_spotConeLocation,  1, _spotCone);
  glUniform4fv(_lightAmbientLocation,  1, _lightAmbient);
  glUniform4fv(_lightDiffuseLocation,  1, _lightDiffuse);
  glUniform4fv(_lightSpecularLocation,  1, _lightSpecular);
  glUseProgram(0);
}
