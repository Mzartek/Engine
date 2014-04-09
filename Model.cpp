#include <Engine/Model.hpp>

engine::Model::Model(void)
{
  matIdentity();
  _context = NULL;
  _shadow = NULL;
}

engine::Model::~Model(void)
{
  unsigned i;
  for(i=0 ; i<_tObject.size(); i++)
    delete _tObject[i];
}

void engine::Model::setGLcontext(GLcontext *context)
{
  _context = context;
}

void engine::Model::setShadowMap(ShadowMap *shadow)
{
  _shadow = shadow;
}

void engine::Model::createObject(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
				 const GLuint &sizeIndexArray, const GLuint *indexArray,
				 const std::string pathTexture,
				 const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess)
{
  Object *newone = new Object();

  newone->setGLcontext(_context);
  newone->setShadowMap(_shadow);
  newone->setTexture(engine::loadTex(pathTexture));
  newone->setAmbient(ambient[0], ambient[1], ambient[2], ambient[3]);
  newone->setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
  newone->setSpecular(specular[0], specular[1], specular[2], specular[3]);
  newone->setShininess(shininess[0]);
  newone->load(sizeVertexArray, vertexArray,
	       sizeIndexArray, indexArray);
  
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

engine::Vector3D<GLfloat> engine::Model::getPosition(void) const
{
  engine::Vector3D<GLfloat> tmp;
  tmp._x = _modelMatrix[12];
  tmp._y = _modelMatrix[13];
  tmp._z = _modelMatrix[14];
  return tmp;
}
  
void engine::Model::display(void) const
{
  unsigned i;
  GLfloat tmp[16];
  
  if(_context == NULL)
    {
      std::cerr << "You need to set the GLcontext before" << std::endl;
      return;
    }

  glUseProgram(_context->getProgramId());

  MultiplyMatrices4by4OpenGL_FLOAT(tmp, _context->VP, _modelMatrix);
  glUniformMatrix4fv(_context->MVPLocation, 1, GL_FALSE, tmp);

  if(_shadow !=NULL)
    {
      MultiplyMatrices4by4OpenGL_FLOAT(tmp, _context->depthVP, _modelMatrix);
      glUniformMatrix4fv(_context->depthMVPLocation, 1, GL_FALSE, tmp);
    }
  
  glUniformMatrix4fv(_context->modelMatrixLocation, 1, GL_FALSE, _modelMatrix);
  
  glUseProgram(0);
  
  for(i=0 ; i<_tObject.size(); i++)
    _tObject[i]->display();
}

void engine::Model::displayShadow(void) const
{
  unsigned i;
  GLfloat tmp[16];
  
  if(_shadow == NULL)
    {
      std::cerr << "You need to set the ShadowMap before" << std::endl;
      return;
    }
      
  glUseProgram(_shadow->getProgramId());
  
  MultiplyMatrices4by4OpenGL_FLOAT(tmp, _shadow->VP, _modelMatrix);
  glUniformMatrix4fv(_shadow->MVPLocation, 1, GL_FALSE, tmp);
  
  glUseProgram(0);
  
  for(i=0 ; i<_tObject.size(); i++)
    _tObject[i]->displayShadow();
}
