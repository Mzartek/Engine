#include <Engine/Graphics/DirLight.hpp>

Engine::Graphics::DirLight::DirLight(const std::shared_ptr<ShaderProgram> &program)
	: Light(program)
{
	for (GLuint i = 0; i < CSM_NUM; i++)
	{
		_projectionMatrix.push_back(glm::mat4());
		_viewMatrix.push_back(glm::mat4());
		_VPMatrix.push_back(glm::mat4());
	}

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

Engine::Graphics::DirLight::~DirLight(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::Graphics::DirLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
}

void Engine::Graphics::DirLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = glm::normalize(dir);
}

const glm::mat4 &Engine::Graphics::DirLight::getProjectionMatrix(GLuint num) const
{
	return _projectionMatrix[num];
}

const glm::mat4 &Engine::Graphics::DirLight::getViewMatrix(GLuint num) const
{
	return _viewMatrix[num];
}

const glm::mat4 &Engine::Graphics::DirLight::getVPMatrix(GLuint num) const
{
	return _VPMatrix[num];
}

const glm::vec3 &Engine::Graphics::DirLight::getColor(void) const
{
	return _lightInfo.color;
}

const glm::vec3 &Engine::Graphics::DirLight::getDirection(void) const
{
	return _lightInfo.direction;
}

void Engine::Graphics::DirLight::updateData(const glm::vec3 &pos, GLfloat dim0, GLfloat dim1, GLfloat dim2)
{
	GLfloat dim[3] = { dim0, dim1, dim2 };

	for (GLuint i = 0; i < CSM_NUM; i++)
	{
		_projectionMatrix[i] = glm::ortho(-dim[i], dim[i], -dim[i], dim[i], -dim[i], dim[i]);
		_viewMatrix[i] = glm::lookAt(pos - _lightInfo.direction, pos, glm::vec3(0.0f, 1.0f, 0.0f));
		_VPMatrix[i] = _projectionMatrix[i] * _viewMatrix[i];
	}

	_lightInfo.shadowMatrix[0] = _VPMatrix[0];
	_lightInfo.shadowMatrix[1] = _VPMatrix[1];
	_lightInfo.shadowMatrix[2] = _VPMatrix[2];
}

void Engine::Graphics::DirLight::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam)
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

void Engine::Graphics::DirLight::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam, const std::vector<std::shared_ptr<Graphics::DepthMap>> &depthMaps)
{
	if (depthMaps.size() != CSM_NUM)
	{
		std::cerr << "Wrong vector of depthMap size" << std::endl;
		abort();
	}

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
	glBindTexture(GL_TEXTURE_2D, depthMaps[0]->getIdDepthTexture());

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMaps[1]->getIdDepthTexture());

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, depthMaps[2]->getIdDepthTexture());

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
