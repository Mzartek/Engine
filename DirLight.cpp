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
  
  if(_shadow==NULL)
    {
      std::cerr << "No need to position the light if you don't use shadowMapping" << std::endl;
      return;
    }
  
  matrixOrtho(projection, -SIZE, SIZE, -SIZE, SIZE, -SIZE, SIZE);
  matrixLoadIdentity(view);
  matrixLookAt(view, position, target, head);
  MultiplyMatrices4by4OpenGL_FLOAT(_VP, projection, view);
}
