#ifndef MODEL
#define MODEL

#include "matrix.h"
#include "Object.hpp"
#include "Vector3D.hpp"

namespace engine
{
  class Model
  {
  private:
    std::vector<Object *> _tObject;
    GLcontext *_context;
    GLfloat _modelMatrix[16];
  public:
    Model();
    ~Model();
    void setGLcontext(GLcontext *context);
    void createObject(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
		      const GLuint &sizeIndexArray, const GLuint *indexArray,
		      const std::string pathTexture,
		      const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess);
    void matIdentity(void);
    void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    Vector3D<GLfloat> getPosition(void) const;
    void display(void) const;
    void displayShadow(void) const;
  };
}
    

#endif
