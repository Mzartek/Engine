#include <Engine/GLObject.hpp>

engine::GLObject::GLObject(void)
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
	_gProgram = NULL;
}

engine::GLObject::~GLObject(void)
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

void engine::GLObject::setShaderProgram(ShaderProgram *gProgram)
{
	_gProgram = gProgram;
	_gNormalTextureLocation = glGetUniformLocation(_gProgram->getId(), "normalTexture");
	_gMaterialTextureLocation = glGetUniformLocation(_gProgram->getId(), "materialTexture");
	_gDepthTextureLocation = glGetUniformLocation(_gProgram->getId(), "depthTexture");
	_gColorTextureLocation = glGetUniformLocation(_gProgram->getId(), "colorTexture");
	_gMatAmbientLocation = glGetUniformLocation(_gProgram->getId(), "matAmbient");
	_gMatDiffuseLocation = glGetUniformLocation(_gProgram->getId(), "matDiffuse");
	_gMatSpecularLocation = glGetUniformLocation(_gProgram->getId(), "matSpecular");
	_gMatShininessLocation = glGetUniformLocation(_gProgram->getId(), "matShininess");
}

void engine::GLObject::setTexture(const GLuint &id)
{
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	_idTexture = id;
}

void engine::GLObject::setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	_matAmbient[0] = x;
	_matAmbient[1] = y;
	_matAmbient[2] = z;
	_matAmbient[3] = w;
}

void engine::GLObject::setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	_matDiffuse[0] = x;
	_matDiffuse[1] = y;
	_matDiffuse[2] = z;
	_matDiffuse[3] = w;
}

void engine::GLObject::setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	_matSpecular[0] = x;
	_matSpecular[1] = y;
	_matSpecular[2] = z;
	_matSpecular[3] = w;
}

void engine::GLObject::setShininess(const GLfloat &x)
{
	_matShininess[0] = x;
}

GLfloat engine::GLObject::getTransparency(void)
{
	return _matDiffuse[3];
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::GLObject::load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray)
{
	_numElement = sizeIndexArray/(GLsizei)sizeof(GLuint);

	// Vertex Array, Vertex Buffer GLObject and Indec Buffer GLObject
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

void engine::GLObject::display(GBuffer *g) const
{
	if (_gProgram == NULL)
	{
		std::cerr << "You need to set the ShaderProgram before" << std::endl;
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, g->getIdFBO());
	glUseProgram(_gProgram->getId());
	glBindVertexArray(_idVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_NORMAL));
	glUniform1i(_gNormalTextureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_MATERIAL));
	glUniform1i(_gMaterialTextureLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_DEPTH));
	glUniform1i(_gDepthTextureLocation, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(_gColorTextureLocation, 3);

	glUniform4fv(_gMatAmbientLocation, 1, _matAmbient);
	glUniform4fv(_gMatDiffuseLocation, 1, _matDiffuse);
	glUniform4fv(_gMatSpecularLocation, 1, _matSpecular);
	glUniform1fv(_gMatShininessLocation, 1, _matShininess);

	glDrawBuffers(2, g->colorAttachment);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void engine::GLObject::displayShadow(Light *l) const
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

	glBindFramebuffer(GL_FRAMEBUFFER, l->getShadowMap()->getIdFBO());
	glUseProgram(l->getShadowMap()->getProgramId());
	glBindVertexArray(_idVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(l->getShadowMap()->getColorTextureLocation(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, l->getShadowMap()->getIdDepthTexture());
	glUniform1i(l->getShadowMap()->getShadowMapLocation(), 1);

	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int engine::comparGLObject(const void *p1, const void *p2)
{
	GLObject **obj1 = (engine::GLObject **)p1;
	GLObject **obj2 = (engine::GLObject **)p2;

	if((*obj1)->_matDiffuse[3] < (*obj2)->_matDiffuse[3])
		return 1;
	if((*obj1)->_matDiffuse[3] > (*obj2)->_matDiffuse[3])
		return -1;
	return 0;
}
