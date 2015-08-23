#include <Engine/Graphics/Texture2D.hpp>

Engine::Graphics::Texture2D::Texture2D(void)
{
}

Engine::Graphics::Texture2D::~Texture2D(void)
{
}

Engine::Graphics::TextureType Engine::Graphics::Texture2D::getType(void) const
{
	return TEXTURE_2D_TYPE;
}

void Engine::Graphics::Texture2D::loadFromFile(const GLchar *path)
{
	SDL_Surface *image = IMG_Load(path);
	if (image == NULL)
	{
		throw std::exception(std::string("Error while loading image: " + std::string(path) + "\n" + IMG_GetError()).c_str());
	}

	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);
	glBindTexture(GL_TEXTURE_2D, _idTexture);

	switch (image->format->format)
	{
	case 386930691:
		glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGB8, image->w, image->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->w, image->h, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case 390076419:
		glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGB8, image->w, image->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->w, image->h, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case 376840196:
		glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGBA8, image->w, image->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->w, image->h, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case 372645892:
		glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGBA8, image->w, image->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->w, image->h, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		break;
	default:
		std::cerr << "Format " << image->format->format << " unknown" << std::endl;
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

	SDL_FreeSurface(image);
}

void Engine::Graphics::Texture2D::loadFromSDL_Surface(const SDL_Surface *surface)
{
	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);
	glBindTexture(GL_TEXTURE_2D, _idTexture);

	switch (surface->format->format)
	{
	case 386930691:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, surface->w, surface->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	case 390076419:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, surface->w, surface->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	case 376840196:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, surface->w, surface->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	case 372645892:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, surface->w, surface->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	default:
		std::cerr << "Format " << surface->format->format << " unknown" << std::endl;
		break;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}