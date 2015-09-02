#include <Engine/Graphics/Light/SpotLight.hpp>

Engine::Graphics::SpotLight::SpotLight(const std::shared_ptr<ShaderProgram> &program)
	: Light(program)
{
	_lightInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _lightInfo, GL_DYNAMIC_DRAW);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "normalTexture"), 0);
	glUniform1i(glGetUniformLocation(_program->getId(), "materialTexture"), 1);
	glUniform1i(glGetUniformLocation(_program->getId(), "depthTexture"), 2);
	glUniform1i(glGetUniformLocation(_program->getId(), "shadowMap"), 3);
}

Engine::Graphics::SpotLight::~SpotLight(void)
{
}

void Engine::Graphics::SpotLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
}

void Engine::Graphics::SpotLight::setPosition(const glm::vec3 &pos)
{
	_lightInfo.position = pos;
}

void Engine::Graphics::SpotLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = glm::normalize(dir);
}

void Engine::Graphics::SpotLight::setSpotCutOff(GLfloat spot)
{
	_lightInfo.spotCutOff = spot;
}

void Engine::Graphics::SpotLight::setMaxDistance(GLfloat maxDistance)
{
	_lightInfo.maxDistance = maxDistance;
}

const glm::mat4 &Engine::Graphics::SpotLight::getProjectionMatrix(void) const
{
	return _projectionMatrix;
}

const glm::mat4 &Engine::Graphics::SpotLight::getViewMatrix(void) const
{
	return _viewMatrix;
}

const glm::mat4 &Engine::Graphics::SpotLight::getVPMatrix(void) const
{
	return _VPMatrix;
}

const glm::vec3 &Engine::Graphics::SpotLight::getColor(void) const
{
	return _lightInfo.color;
}

const glm::vec3 &Engine::Graphics::SpotLight::getPosition(void) const
{
	return _lightInfo.position;
}

const glm::vec3 &Engine::Graphics::SpotLight::getDirection(void) const
{
	return _lightInfo.direction;
}

GLfloat Engine::Graphics::SpotLight::getSpotCutOff(void) const
{
	return _lightInfo.spotCutOff;
}

GLfloat Engine::Graphics::SpotLight::getMaxDistance(void) const
{
	return _lightInfo.maxDistance;
}

void Engine::Graphics::SpotLight::updateData(const std::shared_ptr<DepthMap> &depthMap)
{
	_projectionMatrix = glm::perspective(_lightInfo.spotCutOff * 2, (GLfloat)depthMap->getWidth() / depthMap->getHeight(), 0.1f, _lightInfo.maxDistance);
	_viewMatrix = glm::lookAt(_lightInfo.position, _lightInfo.position + _lightInfo.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	_VPMatrix = _projectionMatrix * _viewMatrix;

	_lightInfo.shadowMatrix = _VPMatrix;
}

void Engine::Graphics::SpotLight::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam)
{
	gbuf->setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBuffer::NORMAL_ID));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBuffer::MATERIAL_ID));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBuffer::DEPTHSTENCIL_ID));

	_mainInfo.IVPMatrix = cam->getIVPMatrix();
	_mainInfo.camPosition = cam->getCameraPosition();
	_mainInfo.withShadowMapping = GL_FALSE;

	_mainInfoBuffer->updateStoreMap(&_mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(Graphics::Screen::Instance().getVertexArray());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::SpotLight::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam, const std::shared_ptr<DepthMap> &depthMap)
{
	gbuf->setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBuffer::NORMAL_ID));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBuffer::MATERIAL_ID));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBuffer::DEPTHSTENCIL_ID));

	// ShadowMap
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, depthMap->getIdDepthTexture());

	_mainInfo.IVPMatrix = cam->getIVPMatrix();
	_mainInfo.camPosition = cam->getCameraPosition();
	_mainInfo.withShadowMapping = GL_TRUE;

	_mainInfoBuffer->updateStoreMap(&_mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(Graphics::Screen::Instance().getVertexArray());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
