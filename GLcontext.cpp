#include <Engine/GLcontext.hpp>

GLuint engine::GLcontext::width = 0;
GLuint engine::GLcontext::height = 0;
GLfloat engine::GLcontext::near = 0;
GLfloat engine::GLcontext::far = 0;

engine::GLcontext::GLcontext(void)
{
  matrixLoadBias(_biasMatrix);
  _program = NULL;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::config(const GLuint &w, const GLuint &h, const GLfloat &n, const GLfloat &f)
{
  width = w;
  height = h;
  near = n;
  far = f;
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glViewport(0, 0, width, height);
}

void engine::GLcontext::clear(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, width, height);
}

void engine::GLcontext::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  
  camMatrixLocation = glGetUniformLocation(_program->getId(), "camMatrix");
  biasLightMatrixLocation = glGetUniformLocation(_program->getId(), "biasLightMatrix");
  modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
  matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
  matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
  matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
  matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
  camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
  lightPositionLocation = glGetUniformLocation(_program->getId(), "lightPosition");
  lightDirectionLocation = glGetUniformLocation(_program->getId(), "lightDirection");
  lightSpotCutOffLocation = glGetUniformLocation(_program->getId(), "lightSpotCutOff");
  lightAmbientLocation = glGetUniformLocation(_program->getId(), "lightAmbient");
  lightDiffuseLocation = glGetUniformLocation(_program->getId(), "lightDiffuse");
  lightSpecularLocation = glGetUniformLocation(_program->getId(), "lightSpecular");
  textureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
  shadowTextureLocation = glGetUniformLocation(_program->getId(), "shadowMap");
}

GLuint engine::GLcontext::getProgramId(void)
{
  return _program->getId();
}
