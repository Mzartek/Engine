#ifndef OBJECT
#define OBJECT

#include "GL.hpp"

namespace engine
{
  class Object
  {
  private:
    GLuint _numElement;
    GLuint _idObject;
    GLuint _idElementObject;
    GLuint _idTextureObject;
  public:
    Object(void);
    ~Object(void);
    void setIdObject(GLuint const &id);
    void setIdElementObject(GLuint const &id, GLuint const &num);
    void setIdTextureObject(GLuint const &id);
    void display(void) const;
  };
}

#endif
