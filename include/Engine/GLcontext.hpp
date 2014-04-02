#ifndef GL_CONTEXT
#define GL_CONTEXT

#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "matrix.h"

namespace engine
{
  class GLcontext
  {
  private:
    ShaderProgram *_program;
    GLfloat _projectionMatrix[16];
    GLint _projectionMatrixLocation;
  public:
    GLcontext(void);
    ~GLcontext(void);
    void setShaderProgram(ShaderProgram *program);
    void adjust(const int &w, const int &h, const float &fov, const float &near, const float &far);
  };
}


#endif
