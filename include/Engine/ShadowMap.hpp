#ifndef SHADOW_MAP
#define SHADOW_MAP

#include "matrix.h"
#include "GL.hpp"
#include "Model.hpp"
#include "Light.hpp"

namespace engine
{
  class ShadowMap
  {
  private:
    GLuint _width;
    GLuint _height;
    GLuint _idFBO;
    GLuint _idDepthTexture;
    GLfloat _projectionMatrix[16];
    ShaderProgram *_program;
    GLint _projectionMatrixLocation;
    GLint _viewMatrixLocation;
    GLint _modelMatrixLocation;
  public:
    ShadowMap(void);
    ~ShadowMap(void);
    void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
    void drawIn(Light *theLight, Model *theModel);
  };
}

#endif
