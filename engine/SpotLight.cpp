#include <Engine/SpotLight.hpp>

engine::SpotLight::SpotLight(void)
{
  _lightSpotCutOff[0] = 45;
}

engine::SpotLight::~SpotLight(void)
{
}

void engine::SpotLight::setSpotCutOff(const float &x)
{
  _lightSpotCutOff[0] = x;
}

GLfloat *engine::SpotLight::getSpotCutOff(void)
{
  return _lightSpotCutOff;
}

void engine::SpotLight::position(void)
{
  GLfloat position[] = {_lightPosition[0], _lightPosition[1], _lightPosition[2]};
  GLfloat target[] = {_lightPosition[0] + _lightDirection[0],
		      _lightPosition[1] + _lightDirection[1],
		      _lightPosition[2] + _lightDirection[2]};
  GLfloat head[] = {0.0, 1.0, 0.0};
  GLfloat projection[16], view[16];

  if(_shadow==NULL)
    {
      std::cerr << "No need to position the light if you don't use shadowMapping" << std::endl;
      return;
    }
    
  matrixPerspective(projection, _lightSpotCutOff[0] * 2, (float)_shadow->getWidth() / _shadow->getHeight(), 0.1, 1200.0);
  matrixLoadIdentity(view);
  matrixLookAt(view, position, target, head);
  MultiplyMatrices4by4OpenGL_FLOAT(_VP, projection, view);
}
