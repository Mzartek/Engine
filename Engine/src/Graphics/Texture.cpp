#include <Engine/Graphics/Texture.hpp>

Engine::Graphics::Texture::Texture(void)
	: _idTexture(0)
{
}

Engine::Graphics::Texture::~Texture(void)
{
	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
}

GLuint Engine::Graphics::Texture::getId(void) const
{
	return _idTexture;
}
