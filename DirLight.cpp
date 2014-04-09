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
  GLfloat lightMatrix[16];
  GLfloat biasLightMatrix[16];

  if(_context == NULL)
    {
      std::cerr << "You need to set the GLcontext before" << std::endl;
      return;
    }

  matrixOrtho(_projectionMatrix, -100, 100, -100, 100, -100, 100);
  matrixLoadIdentity(_viewMatrix);
  matrixLookAt(_viewMatrix, position, target, head);
  
  MultiplyMatrices4by4OpenGL_FLOAT(lightMatrix, _projectionMatrix, _viewMatrix);
  if(_shadow != NULL)
    {
      glUseProgram(_shadow->getProgramId());
      glUniformMatrix4fv(_shadow->lightMatrixLocation, 1, GL_FALSE, lightMatrix);
      glUseProgram(0);
    }
  
  MultiplyMatrices4by4OpenGL_FLOAT(biasLightMatrix, _context->_biasMatrix, lightMatrix);
  glUseProgram(_context->getProgramId());
  glUniformMatrix4fv(_context->biasLightMatrixLocation, 1, GL_FALSE, biasLightMatrix);
  glUniform3fv(_context->lightPositionLocation,  1, _lightPosition);
  glUniform3fv(_context->lightDirectionLocation,  1, _lightDirection);
  glUniform4fv(_context->lightAmbientLocation,  1, _lightAmbient);
  glUniform4fv(_context->lightDiffuseLocation,  1, _lightDiffuse);
  glUniform4fv(_context->lightSpecularLocation,  1, _lightSpecular);
  glUseProgram(0);
}
