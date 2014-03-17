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
    void setIdObject(GLuint const &id);
    void setIdElementObject(GLuint const &id, GLuint const &num);
    void setIdTextureObject(GLuint const &id);
    void setAmbiant(GLfloat const &x, GLfloat const &y, GLfloat const &z, GLfloat const &w);
    void setDiffuse(GLfloat const &x, GLfloat const &y, GLfloat const &z, GLfloat const &w);
    void setSpecular(GLfloat const &x, GLfloat const &y, GLfloat const &z, GLfloat const &w);
    void setShininess(GLfloat const &x);
    void display(void) const;
  };
}

#endif
