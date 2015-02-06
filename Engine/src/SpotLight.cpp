#include <Engine/SpotLight.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>

Engine::SpotLight::SpotLight(ShaderProgram *program)
	: Light(program)
{
	_shadow = new ShadowMap;
	_projectionMatrix = new glm::mat4;
	_viewMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;

	_lightInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _lightInfo, GL_DYNAMIC_DRAW);

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
	glBindVertexArray(0);
}

Engine::SpotLight::~SpotLight(void)
{
	delete _shadow;
	delete _projectionMatrix;
	delete _viewMatrix;
	delete _VPMatrix;

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

void Engine::SpotLight::setSpotCutOff(const GLfloat &spot)
{
	_lightInfo.spotCutOff = spot;
}

void Engine::SpotLight::setMaxDistance(const GLfloat &maxDistance)
{
    _lightInfo.maxDistance = maxDistance;
}

void Engine::SpotLight::setShadowMapping(const GLboolean &shadow)
{
	_lightInfo.withShadowMapping = shadow;
}

void Engine::SpotLight::configShadowMap(const GLuint &width, const GLuint &height) const
{
	_shadow->config(width, height);
}

Engine::ShadowMap *Engine::SpotLight::getShadowMap(void) const
{
	return _shadow;
}

glm::mat4 Engine::SpotLight::getProjectionMatrix(void) const
{
	return *_projectionMatrix;
}

glm::mat4 Engine::SpotLight::getViewMatrix(void) const
{
	return *_viewMatrix;
}

glm::mat4 Engine::SpotLight::getVPMatrix(void) const
{
	return *_VPMatrix;
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

GLfloat Engine::SpotLight::getMaxDistance(void) const
{
    return _lightInfo.maxDistance;
}

void Engine::SpotLight::position(void) const
{
    *_projectionMatrix = glm::perspective(_lightInfo.spotCutOff * 2, (GLfloat)_shadow->getWidth() / _shadow->getHeight(), 0.1f, _lightInfo.maxDistance);
    *_viewMatrix = glm::lookAt(_lightInfo.position, _lightInfo.position + _lightInfo.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	*_VPMatrix =  *_projectionMatrix * *_viewMatrix;
}

void Engine::SpotLight::clear(void) const
{
	_shadow->clear();
}

void Engine::SpotLight::display(GBuffer *gbuf, Camera *cam) const
{
	glm::vec3 camPosition = cam->getCameraPosition();

	gbuf->setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_NORMAL));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_DEPTH_STENCIL));

	struct
	{
		glm::mat4 shadowMatrix;
		glm::mat4 IVPMatrix;
		glm::uvec2 ALIGN(16) screen;
		glm::vec3 ALIGN(16) camPosition;
	} mainInfo;

	// ShadowMap
	if (_lightInfo.withShadowMapping == GL_TRUE)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());

		mainInfo.shadowMatrix = *_VPMatrix;
	}
	mainInfo.IVPMatrix = cam->getIVPMatrix();
	mainInfo.screen = glm::uvec2(gbuf->getWidth(), gbuf->getHeight());
	mainInfo.camPosition = glm::vec3(camPosition.x, camPosition.y, camPosition.z);

	_mainInfoBuffer->updateStoreMap(&mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
