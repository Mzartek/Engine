#include <Engine/Graphics/PostProcessing.hpp>

Engine::Graphics::PostProcessing::PostProcessing(const std::shared_ptr<ShaderProgram> &effectProgram)
	: _effectProgram(effectProgram)
{
	glUseProgram(_effectProgram->getId());
	glUniform1i(glGetUniformLocation(_effectProgram->getId(), "inputTexture"), 0);
}

Engine::Graphics::PostProcessing::~PostProcessing(void)
{
}

void Engine::Graphics::PostProcessing::display(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture)
{
	cbuf->setNormalState();

	glUseProgram(_effectProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glBindVertexArray(Graphics::GraphicsRenderer::Instance().getScreenVertexArray());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::PostProcessing::displayAdditive(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture)
{
	cbuf->setAdditiveState();

	glUseProgram(_effectProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glBindVertexArray(Graphics::GraphicsRenderer::Instance().getScreenVertexArray());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Engine::Graphics::PostProcessing::displayTransparent(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture)
{
	cbuf->setTransparentState();

	glUseProgram(_effectProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glBindVertexArray(Graphics::GraphicsRenderer::Instance().getScreenVertexArray());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}