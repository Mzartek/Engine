#include <Engine/Model.hpp>

engine::Model::Model(void)
{
  _program = NULL;
  _modelMatrixLocation = -1;
  matIdentity();
}

engine::Model::~Model(void)
{
  unsigned i;
  for(i=0 ; i<_tObject.size(); i++)
    delete _tObject[i];
}

void engine::Model::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  _modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
}

void engine::Model::createObject(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
				 const GLuint &sizeIndexArray, const GLuint *indexArray,
				 const std::string pathTexture,
				 const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess)
{
  Object *newone = new Object();

  newone->load(sizeVertexArray, vertexArray,
	       sizeIndexArray, indexArray,
	       _program);
  newone->setTexture(engine::loadTex(pathTexture));
  newone->setAmbient(ambient[0], ambient[1], ambient[2], ambient[3]);
  newone->setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
  newone->setSpecular(specular[0], specular[1], specular[2], specular[3]);
  newone->setShininess(shininess[0]);
  
  _tObject.push_back(newone);
}

void engine::Model::matIdentity(void)
{
  matrixLoadIdentity(_modelMatrix);
}

void engine::Model::matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  matrixTranslate(_modelMatrix, x, y, z);
}

void engine::Model::matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  matrixRotate(_modelMatrix, angle*((GLfloat)M_PI/180), x, y, z);
}

void engine::Model::matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  matrixScale(_modelMatrix, x, y, z);
}

engine::Vector3D<GLfloat> engine::Model::getPosition(void)
{
  engine::Vector3D<GLfloat> tmp;
  tmp._x = _modelMatrix[12];
  tmp._y = _modelMatrix[13];
  tmp._z = _modelMatrix[14];
  return tmp;
}
  
void engine::Model::display(void)
{
  unsigned i;
  
  glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, _modelMatrix);
  _program->use();
  
  for(i=0 ; i<_tObject.size(); i++)
    _tObject[i]->display();
  glUseProgram(0);
}
