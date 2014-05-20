#include <Engine/Model.hpp>

engine::Model::Model(void)
{
	_tObject = new std::vector<Object *>;
	_context = NULL;
	matIdentity();
}

engine::Model::~Model(void)
{
	GLuint i;
	for(i=0 ; i<_tObject->size(); i++)
		delete (*_tObject)[i];
	delete _tObject;
}

void engine::Model::setRenderer(Renderer *context)
{
	_context = context;
}

void engine::Model::createObject(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				 const GLsizei &sizeIndexArray, const GLuint *indexArray,
				 const std::string pathTexture,
				 const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess)
{
	Object *newone = new Object();
	GLuint texture;
  
	loadTextureFromFile(pathTexture, &texture);

	newone->setRenderer(_context);
	newone->setTexture(texture);
	newone->setAmbient(ambient[0], ambient[1], ambient[2], ambient[3]);
	newone->setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
	newone->setSpecular(specular[0], specular[1], specular[2], specular[3]);
	newone->setShininess(shininess[0]);
	newone->load(sizeVertexArray, vertexArray,
		     sizeIndexArray, indexArray);
  
	_tObject->push_back(newone);
}

void engine::Model::sortObject(void)
{
	qsort(&(*_tObject)[0], _tObject->size(), sizeof (*_tObject)[0], comparObject);
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
	matrixRotate(_modelMatrix, angle, x, y, z);
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
	GLuint i;
	GLfloat tmp[16], bias[16];
  
	if(_context == NULL)
	{
		std::cerr << "You need to set the Renderer before display a model" << std::endl;
		return;
	}
	if(_context->getCamera()==NULL)
	{
		std::cerr <<"You need to set a camera to the Renderer before display a model" << std::endl;
		return;
	}

	matrixLoadBias(bias);
  
	glUseProgram(_context->getProgramId());
  
	matrixMultiply(tmp, _context->getCamera()->getMatrix(), _modelMatrix);
	glUniformMatrix4fv(_context->MVPLocation, 1, GL_FALSE, tmp);
    
	if(_context->getDirLight()!=NULL)
		if(_context->getDirLight()->getShadowMap() != NULL)
		{
			matrixMultiply(tmp, _context->getDirLight()->getMatrix(), _modelMatrix);
			matrixMultiply(tmp, bias, tmp);
			glUniformMatrix4fv(_context->dirShadowMVPLocation, 1, GL_FALSE, tmp);
		}
  
	if(_context->getSpotLight()!=NULL)
		if(_context->getSpotLight()->getShadowMap() != NULL)
		{
			matrixMultiply(tmp, _context->getSpotLight()->getMatrix(), _modelMatrix);
			matrixMultiply(tmp, bias, tmp);
			glUniformMatrix4fv(_context->spotShadowMVPLocation, 1, GL_FALSE, tmp);
		}
  
	matrixNormalFromModel(tmp, _modelMatrix);
	glUniformMatrix4fv(_context->modelMatrixLocation, 1, GL_FALSE, _modelMatrix);
	glUniformMatrix3fv(_context->normalMatrixLocation, 1, GL_FALSE, tmp);
  
	glUseProgram(0);
  
	for(i=0 ; i<_tObject->size(); i++)
		(*_tObject)[i]->display();
}

void engine::Model::displayShadow(Light *l) const
{
	GLuint i;
	GLfloat tmp[16];
  
	if(l != NULL)
		if(l->getShadowMap() != NULL)
		{
			glUseProgram(l->getShadowMap()->getProgramId());
			matrixMultiply(tmp, l->getMatrix(), _modelMatrix);
			glUniformMatrix4fv(l->getShadowMap()->MVPLocation, 1, GL_FALSE, tmp);
			glUseProgram(0);
			for(i=0 ; i<_tObject->size(); i++)
				(*_tObject)[i]->displayShadow(l);
		}
}
