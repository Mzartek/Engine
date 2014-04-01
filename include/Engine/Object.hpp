#ifndef OBJECT
#define OBJECT

#include "GL.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
  class Object
  {
  private:
    GLuint _idVAO;
    GLuint _idVBO[2];
    GLuint _idTexture;
    GLfloat _matAmbient[4];
    GLfloat _matDiffuse[4];
    GLfloat _matSpecular[4];
    GLfloat _matShininess[1];
    GLuint _numElement;
    ShaderProgram *_program;
    GLint _matAmbientLocation;
    GLint _matDiffuseLocation;
    GLint _matSpecularLocation;
    GLint _matShininessLocation;
    GLint _vertexAttribLocation;
    GLint _textureAttribLocation;
    GLint _normalAttribLocation;
  public:
    Object(void);
    ~Object(void);
    void setTexture(const GLuint &id);
    void setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setShininess(const GLfloat &x);
    void load(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
	      const GLuint &sizeIndexArray, const GLuint *indexArray,
	      ShaderProgram *program);
    void display(void) const;
  };
}

#endif
