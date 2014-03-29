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
    unsigned _index;
    ShaderProgram *_program;
    GLint _modelMatrixLocation;
    GLfloat _modelMatrix[16];
  public:
    Model();
    ~Model();
    void setShaderProgram(ShaderProgram *program);
    unsigned createObject(const GLfloat *vertexArray, const GLuint &sizeVertexArray,
			  const GLuint *elementArray, const GLuint &sizeElementArray,
			  const std::string pathTexture,
			  const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess);
    void matIdentity(void);
    void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    Vector3D<GLfloat> getPosition(void);
    void display(void);
  };
}
    

#endif
