#include <Engine/Graphics/Screen.hpp>
#include <Engine/Graphics/GraphicsRenderer.hpp>

Engine::Graphics::Screen &Engine::Graphics::Screen::Instance(void)
{
	static Screen instance;
	return instance;
}

Engine::Graphics::Screen::Screen(void)
{
	_vertexBuffer = std::make_shared<Buffer>();
	_colorBuffer = std::make_shared<Buffer>();

	GLfloat vertex[] = {
		-1, -1,
		0, 0,

		1, -1,
		1, 0,

		-1, 1,
		0, 1,

		1, 1,
		1, 1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);
	_colorBuffer->createStore(GL_UNIFORM_BUFFER, nullptr, sizeof(glm::vec4), GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

Engine::Graphics::Screen::~Screen(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}

GLuint Engine::Graphics::Screen::getVertexArray(void)
{
	return _idVAO;
}

void Engine::Graphics::Screen::displayOnScreen(const std::shared_ptr<GBuffer> &gbuffer, const glm::vec4 &color, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	GraphicsRenderer::Instance().setState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuffer->getIdTexture(GBuffer::BACKGROUND_ID));

	_colorBuffer->updateStoreMap(glm::value_ptr(color));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _colorBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayOnScreen(const std::shared_ptr<CBuffer> &cbuffer, const glm::vec4 &color, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	GraphicsRenderer::Instance().setState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cbuffer->getIdTexture());

	_colorBuffer->updateStoreMap(glm::value_ptr(color));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _colorBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayOnCBuffer(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<CBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	cbuffer->setNormalState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, input->getIdTexture());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayOnCBuffer(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<GBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	cbuffer->setNormalState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, input->getIdTexture(GBuffer::BACKGROUND_ID));

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayOnCBufferAdditive(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<CBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	cbuffer->setAdditiveState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, input->getIdTexture());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayOnCBufferAdditive(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<GBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	cbuffer->setAdditiveState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, input->getIdTexture(GBuffer::BACKGROUND_ID));

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayOnCBufferTransparent(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<CBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	cbuffer->setTransparentState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, input->getIdTexture());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayOnCBufferTransparent(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<GBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	cbuffer->setTransparentState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "inputTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, input->getIdTexture(GBuffer::BACKGROUND_ID));

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::Screen::displayGBufferBackground(const std::shared_ptr<GBuffer> &gbuffer, const std::shared_ptr<ShaderProgram> &shaderProgram) const
{
	gbuffer->setBackgroundState();

	glUseProgram(shaderProgram->getId());
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "materialTexture"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram->getId(), "lightTexture"), 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuffer->getIdTexture(GBuffer::MATERIAL_ID));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuffer->getIdTexture(GBuffer::LIGHT_ID));

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	gbuffer->clearLight();
}
