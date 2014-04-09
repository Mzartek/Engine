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
  GLfloat bias[16], projection[16], view[16];

  if(_context == NULL)
    {
      std::cerr << "You need to set the GLcontext before" << std::endl;
      return;
    }
  
  if(_shadow != NULL)
    {
      matrixOrtho(projection, -100, 100, -100, 100, -100, 100);
      matrixLoadIdentity(view);
      matrixLookAt(view, position, target, head);
      
      MultiplyMatrices4by4OpenGL_FLOAT(_context->depthVP, projection, view);
      memcpy(_shadow->VP, _context->depthVP, 16 * sizeof(GLfloat));

      matrixLoadBias(bias);
      MultiplyMatrices4by4OpenGL_FLOAT(_context->depthVP, bias, _context->depthVP);
    }
  
  glUseProgram(_context->getProgramId());
  glUniform3fv(_context->lightPositionLocation,  1, _lightPosition);
  glUniform3fv(_context->lightDirectionLocation,  1, _lightDirection);
  glUniform4fv(_context->lightAmbientLocation,  1, _lightAmbient);
  glUniform4fv(_context->lightDiffuseLocation,  1, _lightDiffuse);
  glUniform4fv(_context->lightSpecularLocation,  1, _lightSpecular);
  glUseProgram(0);
}
