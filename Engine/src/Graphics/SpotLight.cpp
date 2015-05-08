#include <Engine/Graphics/SpotLight.hpp>

Engine::SpotLight::SpotLight(const std::shared_ptr<ShaderProgram> &program)
	: Light(program)
{
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
	_lightInfo.direction = glm::normalize(dir);
}

void Engine::SpotLight::setSpotCutOff(GLfloat spot)
{
	_lightInfo.spotCutOff = spot;
}

void Engine::SpotLight::setMaxDistance(GLfloat maxDistance)
{
	_lightInfo.maxDistance = maxDistance;
}

const glm::mat4 &Engine::SpotLight::getProjectionMatrix(void) const
{
	return _projectionMatrix;
}

const glm::mat4 &Engine::SpotLight::getViewMatrix(void) const
{
	return _viewMatrix;
}

const glm::mat4 &Engine::SpotLight::getVPMatrix(void) const
{
	return _VPMatrix;
}

const glm::vec3 &Engine::SpotLight::getColor(void) const
{
	return _lightInfo.color;
}

const glm::vec3 &Engine::SpotLight::getPosition(void) const
{
	return _lightInfo.position;
}

const glm::vec3 &Engine::SpotLight::getDirection(void) const
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

void Engine::SpotLight::position(const std::shared_ptr<DepthMap> &depthMap)
{
	_projectionMatrix = glm::perspective(_lightInfo.spotCutOff * 2, (GLfloat)depthMap->getWidth() / depthMap->getHeight(), 0.1f, _lightInfo.maxDistance);
	_viewMatrix = glm::lookAt(_lightInfo.position, _lightInfo.position + _lightInfo.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	_VPMatrix = _projectionMatrix * _viewMatrix;

	_lightInfo.shadowMatrix = _VPMatrix;
}

void Engine::SpotLight::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam)
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

	_mainInfo.IVPMatrix = cam->getIVPMatrix();
	_mainInfo.screen = glm::uvec2(gbuf->getWidth(), gbuf->getHeight());
	_mainInfo.camPosition = cam->getCameraPosition();
	_mainInfo.withShadowMapping = GL_FALSE;

	_mainInfoBuffer->updateStoreMap(&_mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::SpotLight::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam, const std::shared_ptr<DepthMap> &depthMap)
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
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, depthMap->getIdDepthTexture());

	_mainInfo.IVPMatrix = cam->getIVPMatrix();
	_mainInfo.screen = glm::uvec2(gbuf->getWidth(), gbuf->getHeight());
	_mainInfo.camPosition = cam->getCameraPosition();
	_mainInfo.withShadowMapping = GL_TRUE;

	_mainInfoBuffer->updateStoreMap(&_mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
