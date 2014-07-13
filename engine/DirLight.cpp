#include <Engine/DirLight.hpp>

engine::DirLight::DirLight(void)
{
	matrixOrtho(_projection, -100, 100, -100, 100, -100, 100);
}

engine::DirLight::~DirLight(void)
{
}

void engine::DirLight::setDimension(GLfloat x, GLfloat y, GLfloat z)
{
	matrixOrtho(_projection, -x, x, -y, y, -z, z);
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::DirLight::config(ShaderProgram *program)
{
	_program = program;
	_positionTextureLocation = glGetUniformLocation(_program->getId(), "positionTexture");
	_normalTextureLocation = glGetUniformLocation(_program->getId(), "normalTexture");
	_materialTextureLocation = glGetUniformLocation(_program->getId(), "materialTexture");
	_shadowMapLocation = glGetUniformLocation(_program->getId(), "shadowMap");
	_shadowMatrixLocation = glGetUniformLocation(_program->getId(), "shadowMatrix");
	_lightTextureLocation = glGetUniformLocation(_program->getId(), "lightTexture");
	_camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
	_lightColorLocation = glGetUniformLocation(_program->getId(), "lightColor");
	_lightDirectionLocation = glGetUniformLocation(_program->getId(), "lightDirection");

	// Configure Layout
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1,  1,
		1,  1
	};
	
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
  
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertex, vertex, GL_STATIC_DRAW);
  
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), BUFFER_OFFSET(0));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::DirLight::position(void)
{
	GLfloat position[] = {_lightPosition[0]-_lightDirection[0],
			      _lightPosition[1]-_lightDirection[1],
			      _lightPosition[2]-_lightDirection[2]};
	GLfloat target[] = {_lightPosition[0], _lightPosition[1], _lightPosition[2]};
	GLfloat head[] = {0.0, 1.0, 0.0};
	GLfloat view[16];
  
	if(_shadow==NULL)
	{
		std::cerr << "No need to position the light if you don't use shadowMapping" << std::endl;
		return;
	}
  
	matrixLoadIdentity(view);
	matrixLookAt(view, position, target, head);
	matrixMultiply(_VP, _projection, view);
}

void engine::DirLight::display(GBuffer *g, Camera *cam)
{
	GLfloat tmp[16];
	if(g == NULL)
	{
		std::cerr << "Bad GBuffer" << std::endl;
		return;
	}
	if(cam == NULL)
	{
		std::cerr << "Bad camera" << std::endl;
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, g->getIdFBO());
	glUseProgram(_program->getId());
	glBindVertexArray(_idVAO);

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_POSITION));
	glUniform1i(_positionTextureLocation, 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_NORMAL));
	glUniform1i(_normalTextureLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_MATERIAL));
	glUniform1i(_materialTextureLocation, 2);

	// ShadowMap
	if(_shadow != NULL)
	{
		matrixLoadBias(tmp);
		matrixMultiply(tmp, tmp, _VP);
		
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());
		glUniform1i(_shadowMapLocation, 3);
		glUniformMatrix4fv(_shadowMatrixLocation, 1, GL_FALSE, tmp);
	}

	// Cam position
	glUniform3f(_camPositionLocation, cam->getPositionCamera()->x, cam->getPositionCamera()->y, cam->getPositionCamera()->z);
	
	// Color
	glUniform3fv(_lightColorLocation, 1, _lightColor);

	// Direction
	glUniform3fv(_lightDirectionLocation, 1, _lightDirection);

	// Drawing
	glDrawBuffers(1, &g->colorAttachment[GBUF_MATERIAL]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
