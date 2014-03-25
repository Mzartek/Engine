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
    void setModelMatrixLocation(ShaderProgram *program, const std::string name);
    unsigned createObject(const GLfloat *vertexArray, const GLuint &sizeVertexArray,
			  const GLuint *elementArray, const GLuint &sizeElementArray,
			  const std::string pathTexture,
			  const GLfloat *ambiant, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess);
    void matIdentity(void);
    void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void matScale(const GLfloat &x);
    void display(void);
  };
}
    

#endif
