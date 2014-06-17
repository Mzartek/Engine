#include <Engine/DirLight.hpp>

engine::DirLight::DirLight(void)
{
	_dim[0] = 100;
	_dim[1] = 100;
	_dim[2] = 100;
}

engine::DirLight::~DirLight(void)
{
}

void engine::DirLight::setDimension(GLfloat x, GLfloat y, GLfloat z)
{
	_dim[0] = x;
	_dim[1] = y;
	_dim[2] = z;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::DirLight::config(ShaderProgram *program)
{
	_program = program;
	_positionTextureLocation = glGetUniformLocation(_program->getId(), "positionTexture");
	_normalTextureLocation = glGetUniformLocation(_program->getId(), "normalTexture");
	_shininessTextureLocation = glGetUniformLocation(_program->getId(), "shininessTexture");
	_shadowMapLocation = glGetUniformLocation(_program->getId(), "shadowMap");
	_shadowMatrixLocation = glGetUniformLocation(_program->getId(), "shadowMatrix");
	_diffuseTextureLocation = glGetUniformLocation(_program->getId(), "diffuseTexture");
	_specularTextureLocation = glGetUniformLocation(_program->getId(), "specularTexture");
	_camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
	_lightColorLocation = glGetUniformLocation(_program->getId(), "lightColor");
	_lightDirectionLocation = glGetUniformLocation(_program->getId(), "lightDirection");

	// Configure Layout
	GLfloat vertex[] = {
		-1, -1,
		0, 0,
		
		1, -1,
		1, 0,
		
		-1,  1,
		0, 1,
		
		1,  1,
		1, 1
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
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(2*sizeof(GLfloat)));

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
	GLfloat projection[16], view[16];
  
	if(_shadow==NULL)
	{
		std::cerr << "No need to position the light if you don't use shadowMapping" << std::endl;
		return;
	}
  
	matrixOrtho(projection, -_dim[0], _dim[0], -_dim[1], _dim[1], -_dim[2], _dim[2]);
	matrixLoadIdentity(view);
	matrixLookAt(view, position, target, head);
	matrixMultiply(_VP, projection, view);
}

void engine::DirLight::display(Camera *cam, GBuffer *g, LBuffer *l)
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
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, l->getIdFBO());
	glUseProgram(_program->getId());
	glBindVertexArray(_idVAO);

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(0)); // Position
	glUniform1i(_positionTextureLocation, 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(1)); // Normal
	glUniform1i(_normalTextureLocation, 1);
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(2)); // Shininess
	glUniform1i(_shininessTextureLocation, 2);

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

	// LBuffer
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, l->getIdTexture(0));
	glUniform1i(_diffuseTextureLocation, 4);
	
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, l->getIdTexture(1));
	glUniform1i(_specularTextureLocation, 5);

	// Cam position
	glUniform3f(_camPositionLocation, cam->getPositionCamera()->x, cam->getPositionCamera()->y, cam->getPositionCamera()->z);
	
	// Color
	glUniform3fv(_lightColorLocation, 1, _lightColor);

	// Direction
	glUniform3fv(_lightDirectionLocation, 1, _lightDirection);

	// Drawing
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLint engine::DirLight::getLightDirectionLocation(void) const
{
	return _lightDirectionLocation;
}
