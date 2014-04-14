#ifndef OBJECT
#define OBJECT

#include "GL.hpp"
#include "GLcontext.hpp"
#include "ShadowMap.hpp"

namespace engine
{
  class Object
  {
  private:
    GLcontext *_context;
    GLuint _idTexture;
    GLuint _idVAO;
    GLuint _idVBO[2];
    GLfloat _matAmbient[4];
    GLfloat _matDiffuse[4];
    GLfloat _matSpecular[4];
    GLfloat _matShininess[1];
    GLuint _numElement;
  public:
    Object(void);
    ~Object(void);
    void setGLcontext(GLcontext *context);
    void setTexture(const GLuint &id);
    void setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setShininess(const GLfloat &x);
    void load(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
	      const GLuint &sizeIndexArray, const GLuint *indexArray);
    void display(void) const;
    void displayShadow(void) const;
  };
}

#endif
