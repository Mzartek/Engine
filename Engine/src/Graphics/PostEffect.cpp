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