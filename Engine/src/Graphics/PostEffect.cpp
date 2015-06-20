#include <Engine/Graphics/PostEffect.hpp>

Engine::Graphics::PostEffect::PostEffect(const std::shared_ptr<ShaderProgram> &effectProgram)
	: _effectProgram(effectProgram)
{
	glUseProgram(_effectProgram->getId());
	glUniform1i(glGetUniformLocation(_effectProgram->getId(), "inputTexture"), 0);
}

Engine::Graphics::PostEffect::~PostEffect(void)
{
}

void Engine::Graphics::PostEffect::display(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture)
{
	cbuf->setAdditiveState();

	glUseProgram(_effectProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glBindVertexArray(Graphics::GraphicsRenderer::Instance().getScreenVertexArray());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}