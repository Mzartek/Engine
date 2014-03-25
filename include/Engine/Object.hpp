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
    GLfloat _mat_ambiant[4];
    GLfloat _mat_diffuse[4];
    GLfloat _mat_specular[4];
    GLfloat _mat_shininess[1];
  public:
    Object(void);
    ~Object(void);
    void setIdObject(const GLuint &id);
    void setIdElementObject(const GLuint &id, const GLuint &num);
    void setIdTextureObject(const GLuint &id);
    void setAmbiant(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setShininess(const GLfloat &x);
    void display(void) const;
  };
}

#endif
