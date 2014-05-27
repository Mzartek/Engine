#include <Engine/SpotLight.hpp>

engine::SpotLight::SpotLight(void)
{
	_lightSpotCutOff[0] = 45;
}

engine::SpotLight::~SpotLight(void)
{
}

#define BUFFER_OFFSET(i) ((GLubyte *)NULL + (i))

void engine::SpotLight::config(ShaderProgram *program)
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
	_lightPositionLocation = glGetUniformLocation(_program->getId(), "lightPosition");
	_lightDirectionLocation = glGetUniformLocation(_program->getId(), "lightDirection");
	_lightSpotCutOffLocation = glGetUniformLocation(_program->getId(), "lightSpotCutOff");

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
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, GLsizei(4*sizeof(GLfloat)), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GLsizei(4*sizeof(GLfloat)), BUFFER_OFFSET(2*sizeof(GLfloat)));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::SpotLight::setSpotCutOff(const float &x)
{
	_lightSpotCutOff[0] = x;
}

GLfloat *engine::SpotLight::getSpotCutOff(void)
{
	return _lightSpotCutOff;
}

void engine::SpotLight::position(void)
{
	GLfloat position[] = {_lightPosition[0], _lightPosition[1], _lightPosition[2]};
	GLfloat target[] = {_lightPosition[0] + _lightDirection[0],
			    _lightPosition[1] + _lightDirection[1],
			    _lightPosition[2] + _lightDirection[2]};
	GLfloat head[] = {0.0, 1.0, 0.0};
	GLfloat projection[16], view[16];

	if(_shadow==NULL)
	{
		std::cerr << "No need to position the light if you don't use shadowMapping" << std::endl;
		return;
	}
    
	matrixPerspective(projection, _lightSpotCutOff[0] * 2, (float)_shadow->getWidth() / (float)_shadow->getHeight(), 0.1f, 1200.0f);
	matrixLoadIdentity(view);
	matrixLookAt(view, position, target, head);
	matrixMultiply(_VP, projection, view);
}

GLint engine::SpotLight::getLightPositionLocation(void) const
{
	return _lightPositionLocation;
}

GLint engine::SpotLight::getLightDirectionLocation(void) const
{
	return _lightDirectionLocation;
}

GLint engine::SpotLight::getLightSpotCutOffLocation(void) const
{
	return _lightSpotCutOffLocation;
}
