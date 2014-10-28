#include <Engine/SpotLight.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>

Engine::SpotLight::SpotLight(ShaderProgram *program)
{
	_lightInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _lightInfo, GL_DYNAMIC_DRAW);

	_program = program;
	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "normalTexture"), 0);
	glUniform1i(glGetUniformLocation(_program->getId(), "materialTexture"), 1);
	glUniform1i(glGetUniformLocation(_program->getId(), "depthTexture"), 2);
	glUniform1i(glGetUniformLocation(_program->getId(), "shadowMap"), 3);

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
}

Engine::SpotLight::~SpotLight(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::SpotLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
}

void Engine::SpotLight::setPosition(const glm::vec3 &pos)
{
	_lightInfo.position = pos;
}

void Engine::SpotLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = dir;
}

void Engine::SpotLight::setSpotCutOff(const float &spot)
{
	_lightInfo.spotCutOff = spot;
}

void Engine::SpotLight::setShadowMapping(const GLboolean &shadow)
{
	_lightInfo.withShadowMapping = shadow;
}

glm::vec3 Engine::SpotLight::getColor(void) const
{
	return _lightInfo.color;
}

glm::vec3 Engine::SpotLight::getPosition(void) const
{
	return _lightInfo.position;
}

glm::vec3 Engine::SpotLight::getDirection(void) const
{
	return _lightInfo.direction;
}

GLfloat Engine::SpotLight::getSpotCutOff(void) const
{
	return _lightInfo.spotCutOff;
}

void Engine::SpotLight::position(void)
{
	*_VPMatrix = glm::perspective(_lightInfo.spotCutOff * 2 * (glm::pi<GLfloat>() / 180), (GLfloat)_shadow->getWidth() / _shadow->getHeight(), 0.1f, 1000.0f) *
		glm::lookAt(_lightInfo.position, _lightInfo.position + _lightInfo.direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Engine::SpotLight::display(GBuffer *gbuf, Camera *cam)
{
	gbuf->setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_NORMAL));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_DEPTH_STENCIL));

	// ShadowMap
	if (_lightInfo.withShadowMapping == GL_TRUE)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());

		_shadowMatrixBuffer->updateStoreMap(_VPMatrix);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _shadowMatrixBuffer->getId());
	}

	_IVPMatrixBuffer->updateStoreMap(glm::value_ptr(glm::inverse(cam->getVPMatrix())));
	_screenBuffer->updateStoreMap(glm::value_ptr(glm::uvec2(gbuf->getWidth(), gbuf->getHeight())));
	_cameraBuffer->updateStoreMap(glm::value_ptr(glm::vec3(cam->getPositionCamera().x, cam->getPositionCamera().y, cam->getPositionCamera().z)));
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _IVPMatrixBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _screenBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, _cameraBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 4, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}