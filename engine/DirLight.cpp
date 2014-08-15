#include <Engine/DirLight.hpp>

engine::DirLight::DirLight(void)
{
	*_projectionMatrix = glm::ortho(-100, 100, -100, 100, -100, 100);
}

engine::DirLight::~DirLight(void)
{
}

void engine::DirLight::setMatrixDimension(const GLfloat &dim)
{
	*_projectionMatrix = glm::ortho(-dim, dim, -dim, dim, -dim, dim);
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::DirLight::config(ShaderProgram *program)
{
	_program = program;
	_normalTextureLocation = glGetUniformLocation(_program->getId(), "normalTexture");
	_materialTextureLocation = glGetUniformLocation(_program->getId(), "materialTexture");
	_depthTextureLocation = glGetUniformLocation(_program->getId(), "depthTexture");
	_shadowMapLocation = glGetUniformLocation(_program->getId(), "shadowMap");
	_shadowMatrixLocation = glGetUniformLocation(_program->getId(), "shadowMatrix");
	_screenLocation = glGetUniformLocation(_program->getId(), "screen");
	_IVPLocation = glGetUniformLocation(_program->getId(), "IVP");
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
	if(_shadow==NULL)
	{
		std::cerr << "No need to position the light if you don't use shadowMapping" << std::endl;
		return;
	}

	*_VPMatrix = *_projectionMatrix * glm::lookAt(*_lightPosition - *_lightDirection, *_lightPosition, glm::vec3(0.0f, 1.0f, 0.0f));
}

void engine::DirLight::display(GBuffer *g, Camera *cam)
{
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

	glDepthMask(GL_FALSE);
	glBindFramebuffer(GL_FRAMEBUFFER, g->getIdFBO());
	glUseProgram(_program->getId());
	glBindVertexArray(_idVAO);

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
	if(_shadow != NULL)
	{
		glm::mat4 bias;
		bias[0] = glm::vec4(0.5f, 0.0f, 0.0f, 0.0f);
		bias[1] = glm::vec4(0.0f, 0.5f, 0.0f, 0.0f);
		bias[2] = glm::vec4(0.0f, 0.0f, 0.5f, 0.0f);
		bias[3] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		glUniformMatrix4fv(_shadowMatrixLocation, 1, GL_FALSE, glm::value_ptr(bias * *_VPMatrix));

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());
		glUniform1i(_shadowMapLocation, 3);
	}

	// Screen
	glUniform2ui(_screenLocation, g->getWidth(), g->getHeight());

	// InverseViewProjection
	glUniformMatrix4fv(_IVPLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(cam->getVPMatrix())));

	// Cam position
	glUniform3f(_camPositionLocation, cam->getPositionCamera().x, cam->getPositionCamera().y, cam->getPositionCamera().z);

	// Color
	glUniform3fv(_lightColorLocation, 1, glm::value_ptr(*_lightColor));

	// Direction
	glUniform3fv(_lightDirectionLocation, 1, glm::value_ptr(*_lightDirection));

	// Drawing
	glDrawBuffers(1, &g->colorAttachment[GBUF_MATERIAL]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDepthMask(GL_TRUE);
}
