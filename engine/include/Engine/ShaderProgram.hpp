#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "GLHead.hpp"

namespace engine
{
  class DLLAPI ShaderProgram
  {
  private:
    GLuint _idProgram;
    GLuint _idVertexShader;
    GLuint _idFragmentShader;
    GLbyte *readText(const std::string filename);
    GLuint loadShader(const std::string filename, GLenum type);
  public:
    ShaderProgram(void);
    ~ShaderProgram(void);
    GLint loadProgram(const std::string vs, const std::string fs);
    GLuint getId(void);
  };
}

#endif
