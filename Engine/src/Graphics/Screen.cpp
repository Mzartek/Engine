#include <Engine/Graphics/Screen.hpp>

Engine::Screen::Screen(const std::shared_ptr<ShaderProgram> &backgroundProgram, const std::shared_ptr<ShaderProgram> &directProgram)
	: _backgroundProgram(backgroundProgram), _directProgram(directProgram)
{
	_vertexBuffer = std::shared_ptr<Buffer>(new Buffer);
	_colorBuffer = std::shared_ptr<Buffer>(new Buffer);

	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);
	_colorBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::vec4), GL_DYNAMIC_DRAW);

	glUseProgram(_backgroundProgram->getId());
	glUniform1i(glGetUniformLocation(_backgroundProgram->getId(), "materialTexture"), 0);
	glUniform1i(glGetUniformLocation(_backgroundProgram->getId(), "lightTexture"), 1);
	glUseProgram(_directProgram->getId());
	glUniform1i(glGetUniformLocation(_directProgram->getId(), "backgroundTexture"), 0);

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glBindVertexArray(0);
}

Engine::Screen::~Screen(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::Screen::background(const std::shared_ptr<GBuffer> &gbuf) const
{
	gbuf->setBackgroundState();

	glUseProgram(_backgroundProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_LIGHT));

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	gbuf->clearLight();
}

void Engine::Screen::display(const std::shared_ptr<Window> &window, const std::shared_ptr<GBuffer> &gbuf, GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
{
	window->setState();

	glUseProgram(_directProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_BACKGROUND));

	glm::vec4 color(r, g, b, a);
	_colorBuffer->updateStoreMap(glm::value_ptr(color));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _colorBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
