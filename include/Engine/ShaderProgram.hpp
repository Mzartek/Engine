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
    char *readText(const std::string filename);
    GLuint loadShader(const std::string filename, GLenum type);
  public:
    ShaderProgram(void);
    ~ShaderProgram(void);
    GLuint getId(void);
    int loadProgram(const std::string vs, const std::string fs);
    void use(void);
  };
}

#endif
