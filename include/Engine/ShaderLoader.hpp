#ifndef SHADER_LOADER
#define SHADER_LOADER

#include "GL.hpp"

namespace engine
{
  class ShaderLoader
  {
  private:
    GLuint _id;
  public:
    ShaderLoader(void);
    ~ShaderLoader(void);
    GLuint getId(void);
    int loadShader(const char* filename, GLenum type);
    static void deleteShader(GLuint id);
  };
}

#endif
