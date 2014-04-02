#ifndef SHADOW_MAP
#define SHADOW_MAP

#include "matrix.h"
#include "GL.hpp"
#include "ShaderProgram.hpp"

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
    GLint projectionMatrixLocation;
  public:
    GLint viewMatrixLocation;
    GLint modelMatrixLocation;
    ShadowMap(void);
    ~ShadowMap(void);
    void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
    GLuint getIdFBO(void);
    GLuint getIdDepthTexture(void);
    GLuint getProgramId(void);
    void clear(void);
  };
}

#endif
