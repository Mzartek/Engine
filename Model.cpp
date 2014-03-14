#include <Engine/Model.hpp>

engine::Model::Model(void)
{
  _index = 0;
  _program = NULL;
  _modelMatrixLocation = -1;
  _modelMatrix = glm::mat4(1.0);
}

engine::Model::~Model(void)
{
  unsigned i;
  for(i=0 ; i<_tObject.size(); i++)
    delete _tObject[i];
}

void engine::Model::setModelMatrixLocation(ShaderProgram *program, char const *name)
{
  _program = program;
  _modelMatrixLocation = glGetUniformLocation(_program->getId(), name);
}

unsigned engine::Model::createObject(GLfloat const *vertexArray, GLuint const &sizeVertexArray,
				     GLuint const *elementArray, GLuint const &sizeElementArray,
				     char const *pathTexture)
{
  unsigned id;
  Object *newone = new Object();
  engine::initBufferObject(GL_ARRAY_BUFFER, sizeVertexArray, &id, (void *)vertexArray);
  newone->setIdObject(id);
  engine::initBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeElementArray, &id, (void *)elementArray);
  newone->setIdElementObject(id, sizeElementArray/sizeof(GLuint));
  engine::loadTex(pathTexture, &id);
  newone->setIdTextureObject(id);
  
  _tObject.push_back(newone);
  return _index++;
}

void engine::Model::matIdentity(void)
{
  _modelMatrix = glm::mat4(1.0);
}

void engine::Model::matTranslate(GLfloat const &x, GLfloat const &y, GLfloat const &z)
{
  _modelMatrix = glm::translate(_modelMatrix, glm::vec3(x, y, z));
}

void engine::Model::matRotate(GLfloat const &angle, GLfloat const &x, GLfloat const &y, GLfloat const &z)
{
  _modelMatrix = glm::rotate(_modelMatrix, angle, glm::vec3(x, y, z));
}

void engine::Model::matScale(GLfloat const &x)
{
  _modelMatrix = glm::scale(_modelMatrix, glm::vec3(x));
}
  
void engine::Model::display(void)
{
  static unsigned i;
  _program->use();
  glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
  for(i=0 ; i<_tObject.size(); i++)
    _tObject[i]->display();
}
