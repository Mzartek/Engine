#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "GL.hpp"

namespace engine
{
  class ShaderProgram
  {
  private:
    GLuint _idProgram;
    GLuint _idVertexShader;
    GLuint _idFragmentShader;
    GLuint loadShader(const char* filename, GLenum type);
  public:
    ShaderProgram(void);
    ~ShaderProgram(void);
    GLuint getId(void);
    int loadProgram(const char* vs, const char* fs);
    void use(void);
  };
}

#endif
