#ifndef OBJECT
#define OBJECT

#include "GL.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
  class Object
  {
  private:
    GLuint _numElement;
    GLuint _idObject;
    GLuint _idElementObject;
    GLuint _idTextureObject;
    GLfloat _matAmbiant[4];
    GLfloat _matDiffuse[4];
    GLfloat _matSpecular[4];
    GLfloat _matShininess[1];
    ShaderProgram *_program;
    GLint _matAmbiantLocation;
    GLint _matDiffuseLocation;
    GLint _matSpecularLocation;
    GLint _matShininessLocation;
  public:
    Object(void);
    ~Object(void);
    void setShaderProgram(ShaderProgram *program);
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
