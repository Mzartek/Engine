#include <Engine/Graphics/DirLight.hpp>

Engine::DirLight::DirLight(ShaderProgram *program)
	: Light(program)
{
	_projectionMatrix = new_ptr_tab(glm::mat4, CSM_NUM);
	_viewMatrix = new_ptr_tab(glm::mat4, CSM_NUM);
	_VPMatrix = new_ptr_tab(glm::mat4, CSM_NUM);

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
	release_ptr(_projectionMatrix);
	release_ptr(_viewMatrix);
	release_ptr(_VPMatrix);

	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::DirLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
}

void Engine::DirLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = glm::normalize(dir);
}

glm::mat4 Engine::DirLight::getProjectionMatrix(const GLuint &num) const
{
	return _projectionMatrix[num];
}

glm::mat4 Engine::DirLight::getViewMatrix(const GLuint &num) const
{
	return _viewMatrix[num];
}

glm::mat4 Engine::DirLight::getVPMatrix(const GLuint &num) const
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

void Engine::DirLight::position(const glm::vec3 &pos, const GLfloat &dim0, const GLfloat &dim1, const GLfloat &dim2)
{
	GLfloat dim[3] = { dim0, dim1, dim2 };

	for (GLuint i = 0; i < CSM_NUM; i++)
	{
		_projectionMatrix[i] = glm::ortho(-dim[i], dim[i], -dim[i], dim[i], -dim[i], dim[i]);
		_viewMatrix[i] = glm::lookAt(pos - _lightInfo.direction, pos, glm::vec3(0.0f, 1.0f, 0.0f));
		_VPMatrix[i] = _projectionMatrix[i] * _viewMatrix[i];
	}

	memcpy(_lightInfo.shadowMatrix, _VPMatrix, 3 * sizeof(glm::mat4));

	/*glm::mat4 mattest;
	mattest = _projectionMatrix[0];
	std::string test =
	std::to_string(mattest[0][0]) + " " + std::to_string(mattest[0][1]) + " " + std::to_string(mattest[0][2]) + " " + std::to_string(mattest[0][3]) + "\n" +
	std::to_string(mattest[1][0]) + " " + std::to_string(mattest[1][1]) + " " + std::to_string(mattest[1][2]) + " " + std::to_string(mattest[1][3]) + "\n" +
	std::to_string(mattest[2][0]) + " " + std::to_string(mattest[2][1]) + " " + std::to_string(mattest[2][2]) + " " + std::to_string(mattest[2][3]) + "\n" +
	std::to_string(mattest[3][0]) + " " + std::to_string(mattest[3][1]) + " " + std::to_string(mattest[3][2]) + " " + std::to_string(mattest[3][3]) + "\n";
	MessageBoxA(NULL, test.c_str(), "OpenGL", MB_OK);
	abort();*/
}

void Engine::DirLight::display(const GBuffer &gbuf, const PerspCamera &cam)
{
	gbuf.setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf.getIdTexture(GBUF_NORMAL));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf.getIdTexture(GBUF_MATERIAL));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf.getIdTexture(GBUF_DEPTH_STENCIL));

	_mainInfo.IVPMatrix = cam.getIVPMatrix();
	_mainInfo.screen = glm::uvec2(gbuf.getWidth(), gbuf.getHeight());
	_mainInfo.camPosition = cam.getCameraPosition();
	_mainInfo.withShadowMapping = GL_FALSE;

	_mainInfoBuffer->updateStoreMap(&_mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::DirLight::display(const GBuffer &gbuf, const std::array<std::shared_ptr<Engine::DepthMap>, CSM_NUM> &array_depthMap, const PerspCamera &cam)
{
	gbuf.setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf.getIdTexture(GBUF_NORMAL));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf.getIdTexture(GBUF_MATERIAL));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf.getIdTexture(GBUF_DEPTH_STENCIL));

	// ShadowMap
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, array_depthMap[0]->getIdDepthTexture());

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, array_depthMap[1]->getIdDepthTexture());

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, array_depthMap[2]->getIdDepthTexture());

	_mainInfo.IVPMatrix = cam.getIVPMatrix();
	_mainInfo.screen = glm::uvec2(gbuf.getWidth(), gbuf.getHeight());
	_mainInfo.camPosition = cam.getCameraPosition();
	_mainInfo.withShadowMapping = GL_TRUE;

	_mainInfoBuffer->updateStoreMap(&_mainInfo);
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainInfoBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
