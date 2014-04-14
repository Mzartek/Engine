#include <Engine/GLcontext.hpp>

engine::GLcontext::GLcontext(void)
{
  _program = NULL;
  _cam = NULL;
  _dlight0 = NULL;
  _slight0 = NULL;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  
  MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
  modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
  normalMatrixLocation = glGetUniformLocation(_program->getId(), "normalMatrix");
  
  matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
  matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
  matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
  matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
  
  camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
  
  dirLightDirectionLocation0 = glGetUniformLocation(_program->getId(), "dirLightDirection0");
  dirLightAmbientLocation0 = glGetUniformLocation(_program->getId(), "dirLightAmbient0");
  dirLightDiffuseLocation0 = glGetUniformLocation(_program->getId(), "dirLightDiffuse0");
  dirLightSpecularLocation0 = glGetUniformLocation(_program->getId(), "dirLightSpecular0");
  dirShadowMVPLocation0 = glGetUniformLocation(_program->getId(), "dirShadowMVP0");
  dirShadowMapLocation0 = glGetUniformLocation(_program->getId(), "dirShadowMap0");
  
  spotLightPositionLocation0 = glGetUniformLocation(_program->getId(), "spotLightPosition0");
  spotLightDirectionLocation0 = glGetUniformLocation(_program->getId(), "spotLightDirection0");
  spotLightSpotCutOffLocation0 = glGetUniformLocation(_program->getId(), "spotLightCutOff0");
  spotLightAmbientLocation0 = glGetUniformLocation(_program->getId(), "spotLightAmbient0");
  spotLightDiffuseLocation0 = glGetUniformLocation(_program->getId(), "spotLightDiffuse0");
  spotLightSpecularLocation0 = glGetUniformLocation(_program->getId(), "spotLightSpecular0");
  spotShadowMVPLocation0 = glGetUniformLocation(_program->getId(), "spotShadowMVP0");
  spotShadowMapLocation0 = glGetUniformLocation(_program->getId(), "spotShadowMap0");
  
  textureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
}

void engine::GLcontext::setCamera(Camera *cam)
{
  _cam = cam;
}

void engine::GLcontext::setDirLight(const GLuint &lightn, DirLight *light)
{
  switch(lightn)
    {
    case LIGHT0:
      _dlight0 = light;
      break;
      
    default:
      std::cerr << "Unknown DirLight to set" << std::endl;
    }
}

void engine::GLcontext::setSpotLight(const GLuint &lightn, SpotLight *light)
{
  switch(lightn)
    {
    case LIGHT0:
      _slight0 = light;
      break;
      
    default:
      std::cerr << "Unknown SpotLight to set" << std::endl;
    }
}

GLuint engine::GLcontext::getProgramId(void)
{
  return _program->getId();
}

engine::Camera *engine::GLcontext::getCamera(void)
{
  return _cam;
}

engine::DirLight *engine::GLcontext::getDirLight(const GLuint &lightn)
{
  switch(lightn)
    {
    case 0:
      return _dlight0;
      
    default:
      std::cerr << "Unknown DirLight to get" << std::endl;
    }
  return NULL;
}

engine::SpotLight *engine::GLcontext::getSpotLight(const GLuint &lightn)
{
  switch(lightn)
    {
    case 0:
      return _slight0;
      
    default:
      std::cerr << "Unknown SpotLight to get" << std::endl;
    }
  return NULL;
}

void engine::GLcontext::shadowClear(void)
{
  if(_dlight0!=NULL)
    if(_dlight0->getShadowMap() != NULL)
      _dlight0->getShadowMap()->clear();
  
  if(_slight0!=NULL)
    if(_slight0->getShadowMap() != NULL)
      _slight0->getShadowMap()->clear();
}

void engine::GLcontext::newLoop(void)
{
  if(_cam==NULL)
    {
      std::cerr << "You need to set a camera first\n" << std::endl;
      return;
    }
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, _cam->getWidth(), _cam->getHeight());
  GLfloat camera[] = {_cam->getPositionCamera()._x, _cam->getPositionCamera()._y, _cam->getPositionCamera()._z};
  
  glUseProgram(_program->getId());
  
  glUniform3fv(camPositionLocation, 1, camera);
  
  if(_dlight0!=NULL)
    {
      glUniform3fv(dirLightDirectionLocation0, 1, _dlight0->getDirection());
      glUniform4fv(dirLightAmbientLocation0, 1, _dlight0->getAmbient());
      glUniform4fv(dirLightDiffuseLocation0, 1, _dlight0->getDiffuse());
      glUniform4fv(dirLightSpecularLocation0, 1, _dlight0->getSpecular());
    }

  if(_slight0!=NULL)
    {
      glUniform3fv(spotLightPositionLocation0, 1, _slight0->getPosition());
      glUniform3fv(spotLightDirectionLocation0, 1, _slight0->getDirection());
      glUniform1fv(spotLightSpotCutOffLocation0, 1, _slight0->getSpotCutOff());
      glUniform4fv(spotLightAmbientLocation0, 1, _slight0->getAmbient());
      glUniform4fv(spotLightDiffuseLocation0, 1, _slight0->getDiffuse());
      glUniform4fv(spotLightSpecularLocation0, 1, _slight0->getSpecular());
    }
  
  glUseProgram(0);
}
