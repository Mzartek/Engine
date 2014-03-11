#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "GL.hpp"
#include "ShaderLoader.hpp"

namespace engine
{
  class ShaderProgram
  {
  private:
    GLuint _id;
  public:
    ShaderProgram(void);
    ~ShaderProgram(void);
    GLuint getId(void);
    void reset(void);
    void attachShader(ShaderLoader shader);
    void detachShader(ShaderLoader shader);
    int link(void);
    void use(void);
  };
}

#endif
