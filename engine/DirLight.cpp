#include <Engine/DirLight.hpp>

engine::DirLight::DirLight(void)
{
}

engine::DirLight::~DirLight(void)
{
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::DirLight::config(ShaderProgram *program)
{
	_program = program;
	// From GBuffer
	_normalTextureLocation = glGetUniformLocation(_program->getId(), "normalTexture");
	_materialTextureLocation = glGetUniformLocation(_program->getId(), "materialTexture");
	_depthTextureLocation = glGetUniformLocation(_program->getId(), "depthTexture");
	// ShadowMap
	_shadowMapLocation = glGetUniformLocation(_program->getId(), "shadowMap");
	// Matrix
	_shadowMatrixLocation = glGetUniformLocation(_program->getId(), "shadowMatrix");
	_IVPMatrixLocation = glGetUniformLocation(_program->getId(), "IVPMatrix");
	// Screen Info
	_screenLocation = glGetUniformLocation(_program->getId(), "screen");
	// Cam Info
	_camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
	// Light Info
	_lightInfoIndex = glGetUniformBlockIndex(_program->getId(), "lightInfo");

	if (glIsBuffer(_idLightInfoBuffer))
		glDeleteBuffers(1, &_idLightInfoBuffer);
	glGenBuffers(1, &_idLightInfoBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, _idLightInfoBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof _lightInfo, &_lightInfo, GL_DYNAMIC_DRAW);

	// Configure Layout
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1,  1,
		1,  1,
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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::DirLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
	if (glIsBuffer(_idLightInfoBuffer))
	{
		glBindBuffer(GL_UNIFORM_BUFFER, _idLightInfoBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof _lightInfo, &_lightInfo);
	}
}

void engine::DirLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = dir;
	if (glIsBuffer(_idLightInfoBuffer))
	{
		glBindBuffer(GL_UNIFORM_BUFFER, _idLightInfoBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof _lightInfo, &_lightInfo);
	}
}

glm::vec3 engine::DirLight::getColor(void) const
{
	return _lightInfo.color;
}

glm::vec3 engine::DirLight::getDirection(void) const
{
	return _lightInfo.direction;
}

void engine::DirLight::activateShadowMapping(const GLboolean &shadow)
{
	_lightInfo.withShadowMapping = shadow;
	if (glIsBuffer(_idLightInfoBuffer))
	{
		glBindBuffer(GL_UNIFORM_BUFFER, _idLightInfoBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof _lightInfo, &_lightInfo);
	}
}

void engine::DirLight::position(const glm::vec3 &position, const GLfloat &dim)
{
	if(_shadow==NULL)
	{
		std::cerr << "Need to config the ShadowMap before positioning" << std::endl;
		exit(1);
	}

	*_VPMatrix = glm::ortho(-dim, dim, -dim, dim, -dim, dim)
		* glm::lookAt(position - _lightInfo.direction, position, glm::vec3(0.0f, 1.0f, 0.0f));
}

void engine::DirLight::display(GBuffer *g, Camera *cam)
{
	if (_program == NULL)
	{
		std::cerr << "Need to config the SpotLight before displaying" << std::endl;
		exit(1);
	}
	if (g == NULL)
	{
		std::cerr << "Bad GBuffer" << std::endl;
		exit(1);
	}
	if (cam == NULL)
	{
		std::cerr << "Bad camera" << std::endl;
		exit(1);
	}

	glDepthMask(GL_FALSE);
	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_NORMAL));
	glUniform1i(_normalTextureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_MATERIAL));
	glUniform1i(_materialTextureLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, g->getIdTexture(GBUF_DEPTH));
	glUniform1i(_depthTextureLocation, 2);

	// ShadowMap
	if (_lightInfo.withShadowMapping == GL_TRUE)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());
		glUniform1i(_shadowMapLocation, 3);

		glm::mat4 bias;
		bias[0] = glm::vec4(0.5f, 0.0f, 0.0f, 0.0f);
		bias[1] = glm::vec4(0.0f, 0.5f, 0.0f, 0.0f);
		bias[2] = glm::vec4(0.0f, 0.0f, 0.5f, 0.0f);
		bias[3] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		glUniformMatrix4fv(_shadowMatrixLocation, 1, GL_FALSE, glm::value_ptr(bias * *_VPMatrix));
	}

	// InverseViewProjection
	glUniformMatrix4fv(_IVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(cam->getVPMatrix())));

	// Screen
	glUniform2ui(_screenLocation, g->getWidth(), g->getHeight());

	// Cam position
	glUniform3f(_camPositionLocation, cam->getPositionCamera().x, cam->getPositionCamera().y, cam->getPositionCamera().z);

	// Light Info
	glBindBufferBase(GL_UNIFORM_BUFFER, _lightInfoIndex, _idLightInfoBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, g->getIdFBO());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glDepthMask(GL_TRUE);
}
