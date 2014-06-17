#include <Engine/Object.hpp>

engine::Object::Object(void)
{
	GLuint i;
	_idTexture = 0;
	_idVAO = 0;
	_idVBO = 0;
	_idIBO = 0;
	for(i=0 ; i<4 ; i++)
	{
		_matAmbient[i]=1.0;
		_matDiffuse[i]=1.0;
		_matSpecular[i]=1.0;
	}
	_matShininess[0]=1.0;
	_program = NULL;
}

engine::Object::~Object(void)
{
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	if(glIsBuffer(_idIBO))
		glDeleteBuffers(1, &_idIBO);
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
}

void engine::Object::setShaderProgram(ShaderProgram *program)
{
	_program = program;
	_matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
	_matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
	_matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
	_colorTextureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
	_lightDiffuseTextureLocation = glGetUniformLocation(_program->getId(), "lightDiffuseTexture");
	_lightSpecularTextureLocation = glGetUniformLocation(_program->getId(), "lightSpecularTexture");
}

void engine::Object::setTexture(const GLuint &id)
{
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	_idTexture = id;
}

void engine::Object::setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	_matAmbient[0] = x;
	_matAmbient[1] = y;
	_matAmbient[2] = z;
	_matAmbient[3] = w;
}

void engine::Object::setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	_matDiffuse[0] = x;
	_matDiffuse[1] = y;
	_matDiffuse[2] = z;
	_matDiffuse[3] = w;
}

void engine::Object::setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	_matSpecular[0] = x;
	_matSpecular[1] = y;
	_matSpecular[2] = z;
	_matSpecular[3] = w;
}

void engine::Object::setShininess(const GLfloat &x)
{
	_matShininess[0] = x;
}

GLfloat engine::Object::getTransparency(void)
{
	return _matDiffuse[3];
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::Object::load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray)
{
	_numElement = sizeIndexArray/(GLsizei)sizeof(GLuint);
  
	// Vertex Array, Vertex Buffer Object and Indec Buffer Object
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
  
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeVertexArray, vertexArray, GL_STATIC_DRAW);
  
	if(glIsBuffer(_idIBO))
		glDeleteBuffers(1, &_idIBO);
	glGenBuffers(1, &_idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexArray, indexArray, GL_STATIC_DRAW);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(5 * sizeof(GLfloat)));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::Object::display(LBuffer *l) const
{
	if(_program == NULL)
	{
		std::cerr << "You need to set the ShaderProgram before" << std::endl;
		return;
	}
  
	glUseProgram(_program->getId());
  
	glBindVertexArray(_idVAO);
	
	glUniform4fv(_matAmbientLocation,  1, _matAmbient);
	glUniform4fv(_matDiffuseLocation,  1, _matDiffuse);
	glUniform4fv(_matSpecularLocation,  1, _matSpecular);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(_colorTextureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, l->getIdTexture(0));
	glUniform1i(_lightDiffuseTextureLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, l->getIdTexture(1));
	glUniform1i(_lightSpecularTextureLocation, 2);

	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
  
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
  
	glBindVertexArray(0);
  
	glUseProgram(0);
}

void engine::Object::displayOnGBuffer(GBuffer *g) const
{	
	if(g == NULL)
	{
		std::cerr <<"Bad GBuffer!" << std::endl;
		return;
	}
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g->getIdFBO());
	glUseProgram(g->getProgramId());
	glBindVertexArray(_idVAO);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(g->getColorTextureLocation(), 0);
	
	glUniform1fv(g->getShininessLocation(), 1, _matShininess);
        
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void engine::Object::displayShadow(Light *l) const
{
	if(l == NULL)
	{
		std::cerr << "Bad Light!" << std::endl;
		return;
	}
	if(l->getShadowMap() == NULL)
	{
		std::cerr << "You need to config the ShadowMap before!" << std::endl;
		return;
	}
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, l->getShadowMap()->getIdFBO());
	glUseProgram(l->getShadowMap()->getProgramId());
	glBindVertexArray(_idVAO);
	
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

int engine::comparObject(const void *p1, const void *p2)
{
	Object **obj1 = (engine::Object **)p1;
	Object **obj2 = (engine::Object **)p2;

	if((*obj1)->_matDiffuse[3] < (*obj2)->_matDiffuse[3])
		return 1;
	if((*obj1)->_matDiffuse[3] > (*obj2)->_matDiffuse[3])
		return -1;
	return 0;
}
