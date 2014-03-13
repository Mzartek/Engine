#ifndef MODEL
#define MODEL

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "GL.hpp"
#include "Object.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
  class Model
  {
  private:
    std::vector<Object *> _tObject;
    unsigned _index;
    ShaderProgram *_program;
    GLint _modelMatrixLocation;
    glm::mat4 _modelMatrix;
  public:
    Model();
    ~Model();
    void setModelMatrixLocation(ShaderProgram *program, char const *name);
    unsigned createObject(GLfloat const *vertexArray, GLuint const &sizeVertexArray,
			  GLuint const *elementArray, GLuint const &sizeElementArray,
			  char const *pathTexture);
    void matIdentity(void);
    void matTranslate(GLfloat const &x, GLfloat const &y, GLfloat const &z);
    void matRotate(GLfloat const &angle, GLfloat const &x, GLfloat const &y, GLfloat const &z);
    void matScale(GLfloat const &x);
    void display(void);
  };
}
    

#endif
