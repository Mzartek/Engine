#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "GL.hpp"
#include "ShaderObject.hpp"

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
    void attachShader(ShaderObject *shader);
    void detachShader(ShaderObject *shader);
    int link(void);
    void use(void);
  };
}

#endif
