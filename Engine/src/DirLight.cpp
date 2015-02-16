#include <Engine/DirLight.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>

Engine::DirLight::DirLight(ShaderProgram *program)
	: Light(program)
{
	_shadow = new ShadowMap[CSM_NUM];
	_projectionMatrix = new glm::mat4[CSM_NUM];
	_viewMatrix = new glm::mat4[CSM_NUM];
	_VPMatrix = new glm::mat4[CSM_NUM];

	_mainInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _mainInfo, GL_DYNAMIC_DRAW);
	_lightInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _lightInfo, GL_DYNAMIC_DRAW);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "normalTexture"), 0);
	glUniform1i(glGetUniformLocation(_program->getId(), "materialTexture"), 1);
	glUniform1i(glGetUniformLocation(_program->getId(), "depthTexture"), 2);
	glUniform1i(glGetUniformLocation(_program->getId(), "shadowMap0"), 3);
	glUniform1i(glGetUniformLocation(_program->getId(), "shadowMap1"), 4);
	glUniform1i(glGetUniformLocation(_program->getId(), "shadowMap2"), 5);

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glBindVertexArray(0);
}

Engine::DirLight::~DirLight(void)
{
	delete[] _shadow;
	delete[] _projectionMatrix;
	delete[] _viewMatrix;
	delete[] _VPMatrix;

	glDeleteVertexArrays(1, &_idVAO);
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

void Engine::DirLight::configShadowMap(const GLuint &width, const GLuint &height) const
{
	for (GLuint i = 0; i < CSM_NUM; i++)
		_shadow[i].config(width, height);
}

Engine::ShadowMap *Engine::DirLight::getShadowMap(const GLuint num) const
{
	return &_shadow[num];
}

glm::mat4 Engine::DirLight::getProjectionMatrix(const GLuint num) const
{
	return _projectionMatrix[num];
}

glm::mat4 Engine::DirLight::getViewMatrix(const GLuint num) const
{
	return _viewMatrix[num];
}

glm::mat4 Engine::DirLight::getVPMatrix(const GLuint num) const
{
	return _VPMatrix[num];
}

glm::vec3 Engine::DirLight::getColor(void) const
{
	return _lightInfo.color;
}

glm::vec3 Engine::DirLight::getDirection(void) const
{
	return _lightInfo.direction;
}

void Engine::DirLight::position(Camera *cam, const GLfloat &dim) const
{
    glm::vec3 position;
    GLfloat test_dim[3];

	glm::vec3 camPosition = cam->getCameraPosition();
    glm::vec3 camDirection = cam->getViewVector();
    GLfloat n = cam->getNear();

	camDirection = glm::normalize(glm::vec3(camDirection.x, 0, camDirection.z));

    position = camPosition + camDirection * n;

	test_dim[0] = dim / 3;
    test_dim[1] = dim / 2;
    test_dim[2] = dim;

	for (GLuint i = 0; i < CSM_NUM; i++)
	{
		_projectionMatrix[i] = glm::ortho(-test_dim[i], test_dim[i], -test_dim[i], test_dim[i], -test_dim[i], test_dim[i]);
		_viewMatrix[i] = glm::lookAt(position - _lightInfo.direction, position, glm::vec3(0.0f, 1.0f, 0.0f));
		_VPMatrix[i] = _projectionMatrix[i] * _viewMatrix[i];
	}
}

void Engine::DirLight::clear(void) const
{
	for (GLuint i = 0; i < CSM_NUM; i++)
		_shadow[i].clear();
}

void Engine::DirLight::display(GBuffer *gbuf, Camera *cam)
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

	// ShadowMap
	if (_lightInfo.withShadowMapping == GL_TRUE)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow[0].getIdDepthTexture());

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _shadow[1].getIdDepthTexture());

		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, _shadow[2].getIdDepthTexture());

		memcpy(_mainInfo.shadowMatrix, _VPMatrix, 3 * sizeof(glm::mat4));
	}
	_mainInfo.IVPMatrix = cam->getIVPMatrix();
	_mainInfo.screen = glm::uvec2(gbuf->getWidth(), gbuf->getHeight());
	_mainInfo.camPosition = glm::vec3(camPosition.x, camPosition.y, camPosition.z);

	_mainInfoBuffer->updateStoreMap(&_mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
