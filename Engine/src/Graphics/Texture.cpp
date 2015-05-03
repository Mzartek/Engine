#include <Engine/Graphics/Texture.hpp>

Engine::Texture::Texture(void)
	: _idTexture(0)
{
}

Engine::Texture::~Texture(void)
{
	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
}

GLuint Engine::Texture::getId(void) const
{
	return _idTexture;
}
