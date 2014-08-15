#include <Engine/SpotLight.hpp>

engine::SpotLight::SpotLight(void)
{
	_lightSpotCutOff = 45;
}

engine::SpotLight::~SpotLight(void)
{
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::SpotLight::config(ShaderProgram *program)
{
	_program = program;
	_normalTextureLocation = glGetUniformLocation(_program->getId(), "normalTexture");
	_materialTextureLocation = glGetUniformLocation(_program->getId(), "materialTexture");
	_depthTextureLocation = glGetUniformLocation(_program->getId(), "depthTexture");
	_shadowMapLocation = glGetUniformLocation(_program->getId(), "shadowMap");
	_shadowMatrixLocation = glGetUniformLocation(_program->getId(), "shadowMatrix");
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
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(2*sizeof(GLfloat)));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::SpotLight::setSpotCutOff(const float &x)
{
	_lightSpotCutOff = x;
}

GLfloat engine::SpotLight::getSpotCutOff(void) const
{
	return _lightSpotCutOff;
}

void engine::SpotLight::position(void)
{
	if(_shadow==NULL)
	{
		std::cerr << "No need to position the light if you don't use shadowMapping" << std::endl;
		return;
	}
    
	*_VPMatrix = glm::perspective(_lightSpotCutOff * 2, (GLfloat)_shadow->getWidth() / _shadow->getHeight(), 0.1f, 1200.0f) *
		glm::lookAt(*_lightPosition, *_lightPosition + *_lightDirection, glm::vec3(0.0f, 1.0f , 0.0f));
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
