#include <Engine/DirLight.hpp>

engine::DirLight::DirLight(void)
{
}

engine::DirLight::~DirLight(void)
{
}

void engine::DirLight::position(void)
{
  GLfloat position[] = {_lightPosition[0]-_lightDirection[0],
			_lightPosition[1]-_lightDirection[1],
			_lightPosition[2]-_lightDirection[2]};
  GLfloat target[] = {_lightPosition[0], _lightPosition[1], _lightPosition[2]};
  GLfloat head[] = {0.0, 1.0, 0.0};
  GLfloat projection[16], view[16];
  
  matrixOrtho(projection, -100, 100, -100, 100, -100, 100);
  matrixLoadIdentity(view);
  matrixLookAt(view, position, target, head);

  if(_shadow!=NULL)
    MultiplyMatrices4by4OpenGL_FLOAT(_VP, projection, view);
}
