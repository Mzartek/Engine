#include <Engine/DirLight.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>

Engine::DirLight::DirLight(void)
{
}

Engine::DirLight::~DirLight(void)
{
}

void Engine::DirLight::config(ShaderProgram *program)
{
	Light::config(program);
	_lightInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _lightInfo, GL_DYNAMIC_DRAW);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "normalTexture"), 0);
	glUniform1i(glGetUniformLocation(_program->getId(), "materialTexture"), 1);
	glUniform1i(glGetUniformLocation(_program->getId(), "depthTexture"), 2);
	glUniform1i(glGetUniformLocation(_program->getId(), "shadowMap"), 3);
	glUseProgram(0);
}

void Engine::DirLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
}

void Engine::DirLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = dir;
}

void Engine::DirLight::setShadowMapping(const GLboolean &shadow)
{
	_lightInfo.withShadowMapping = shadow;
}

glm::vec3 Engine::DirLight::getColor(void) const
{
	return _lightInfo.color;
}

glm::vec3 Engine::DirLight::getDirection(void) const
{
	return _lightInfo.direction;
}

void Engine::DirLight::position(const glm::vec3 &position, const GLfloat &dim)
{
	*_VPMatrix = glm::ortho(-dim, dim, -dim, dim, -dim, dim)
		* glm::lookAt(position - _lightInfo.direction, position, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Engine::DirLight::display(GBuffer *gbuf, Camera *cam)
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
	glBindVertexArray(0);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}