#include <Engine/DirLight.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>

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

	// Layout
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);

	glBindVertexArray(_idVAO);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));

	glBindVertexArray(0);

	// LightInfo Buffer
	_lightInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _lightInfo, GL_DYNAMIC_DRAW);

	_normalTextureLocation = glGetUniformLocation(_program->getId(), "normalTexture");
	_materialTextureLocation = glGetUniformLocation(_program->getId(), "materialTexture");
	_depthTextureLocation = glGetUniformLocation(_program->getId(), "depthTexture");
	_shadowMapLocation = glGetUniformLocation(_program->getId(), "shadowMap");
	_shadowMatrixLocation = glGetUniformLocation(_program->getId(), "shadowMatrix");
	_IVPMatrixLocation = glGetUniformLocation(_program->getId(), "IVPMatrix");
	_screenLocation = glGetUniformLocation(_program->getId(), "screen");
	_camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
	_lightInfoBlockIndex = glGetUniformBlockIndex(_program->getId(), "lightInfo");
}

#undef BUFFER_OFFSET

void engine::DirLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
}

void engine::DirLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = dir;
}

void engine::DirLight::setShadowMapping(const GLboolean &shadow)
{
	_lightInfo.withShadowMapping = shadow;
}

glm::vec3 engine::DirLight::getColor(void) const
{
	return _lightInfo.color;
}

glm::vec3 engine::DirLight::getDirection(void) const
{
	return _lightInfo.direction;
}

void engine::DirLight::position(const glm::vec3 &position, const GLfloat &dim)
{
	*_VPMatrix = glm::ortho(-dim, dim, -dim, dim, -dim, dim)
		* glm::lookAt(position - _lightInfo.direction, position, glm::vec3(0.0f, 1.0f, 0.0f));
}

void engine::DirLight::display(GBuffer *gbuf, Camera *cam)
{
	gbuf->setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_NORMAL));
	glUniform1i(_normalTextureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));
	glUniform1i(_materialTextureLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_DEPTH_STENCIL));
	glUniform1i(_depthTextureLocation, 2);

	// ShadowMap
	if (_lightInfo.withShadowMapping == GL_TRUE)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());
		glUniform1i(_shadowMapLocation, 3);

		glUniformMatrix4fv(_shadowMatrixLocation, 1, GL_FALSE, glm::value_ptr(*_VPMatrix));
	}

	// InverseViewProjection
	glUniformMatrix4fv(_IVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(cam->getVPMatrix())));

	// Screen
	glUniform2ui(_screenLocation, gbuf->getWidth(), gbuf->getHeight());

	// Cam position
	glUniform3f(_camPositionLocation, cam->getPositionCamera().x, cam->getPositionCamera().y, cam->getPositionCamera().z);

	// Light Info
	_lightInfoBuffer->updateStoreMap(&_lightInfo);
	glBindBufferBase(GL_UNIFORM_BUFFER, _lightInfoBlockIndex, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
