#ifndef SHADER_OBJECT
#define SHADER_OBJECT

#include "GL.hpp"

namespace engine
{
  class ShaderObject
  {
  private:
    GLuint _id;
  public:
    ShaderObject(void);
    ~ShaderObject(void);
    GLuint getId(void);
    int loadShader(const char* filename, GLenum type);
    void deleteShader(void);
  };
}

#endif
