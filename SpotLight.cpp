#include <Engine/SpotLight.hpp>

engine::SpotLight::SpotLight(void)
{
  _lightSpotCutOff[0] = 45;
}

engine::SpotLight::~SpotLight(void)
{
}

void engine::SpotLight::setCone(const float &x)
{
  _lightSpotCutOff[0] = x;
}

void engine::SpotLight::position(void)
{
  GLfloat position[] = {_lightPosition[0], _lightPosition[1], _lightPosition[2]};
  GLfloat target[] = {_lightPosition[0] + _lightDirection[0],
		      _lightPosition[1] + _lightDirection[1],
		      _lightPosition[2] + _lightDirection[2]};
  GLfloat head[] = {0.0, 1.0, 0.0};
  GLfloat lightMatrix[16];
  GLfloat biasLightMatrix[16];

  if(_context == NULL)
    {
      std::cerr << "You need to set the GLcontext before" << std::endl;
      return;
    }

  matrixPerspective(_projectionMatrix, _lightSpotCutOff[0] * 2, (float)GLcontext::width / GLcontext::height, GLcontext::near, GLcontext::far);
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
  glUniformMatrix4fv(_context->biasLightMatrixLocation, 1, GL_FALSE, lightMatrix);
  glUniform3fv(_context->lightPositionLocation,  1, _lightPosition);
  glUniform3fv(_context->lightDirectionLocation,  1, _lightDirection);
  glUniform1fv(_context->lightSpotCutOffLocation,  1, _lightSpotCutOff);
  glUniform4fv(_context->lightAmbientLocation,  1, _lightAmbient);
  glUniform4fv(_context->lightDiffuseLocation,  1, _lightDiffuse);
  glUniform4fv(_context->lightSpecularLocation,  1, _lightSpecular);
  glUseProgram(0);
}
