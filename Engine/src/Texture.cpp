#include <Engine/Texture.hpp>

enum pixelFormat { UNKNOWN, RGB, BGR, RGBA };

static pixelFormat testFormat(const GLuint &f)
{
	switch (f)
	{
	case 386930691:
		return RGB;
	case 390076419:
		return BGR;
	case 376840196:
		return RGBA;
	case 372645892:
		return RGBA;
	default:
		return UNKNOWN;
	}
}

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

void Engine::Texture::load2DTextureFromFile(const GLchar *path)
{
	SDL_Surface *image = IMG_Load(&path[0]);
	if (image == NULL)
	{
		std::cerr << "Error while loading image: " << path << std::endl;
		std::cerr << IMG_GetError() << std::endl;
		exit(1);
	}

	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);
	glBindTexture(GL_TEXTURE_2D, _idTexture);

	switch (testFormat(image->format->format))
	{
	case RGB:
		glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGB8, image->w, image->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->w, image->h, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case BGR:
		glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGB8, image->w, image->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->w, image->h, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case RGBA:
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

void Engine::Texture::load2DTextureFromSDL_Surface(const SDL_Surface *surface)
{
	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);
	glBindTexture(GL_TEXTURE_2D, _idTexture);

	switch (testFormat(surface->format->format))
	{
	case RGB:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, surface->w, surface->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	case BGR:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, surface->w, surface->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	case RGBA:
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

void Engine::Texture::loadCubeTextureFromFiles(
	const GLchar *posx, const GLchar *negx,
	const GLchar *posy, const GLchar *negy,
	const GLchar *posz, const GLchar *negz)
{
	GLenum cube_map_target[] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	SDL_Surface *image[6];
	image[0] = IMG_Load(posx);
	image[1] = IMG_Load(negx);
	image[2] = IMG_Load(posy);
	image[3] = IMG_Load(negy);
	image[4] = IMG_Load(posz);
	image[5] = IMG_Load(negz);

	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _idTexture);

	for (int i = 0; i<6; i++)
	{
		if (image[i] == NULL)
		{
			std::cerr << "Error while loading image: ";
			switch (i)
			{
			case 0:
				std::cerr << posx << std::endl;
				break;
			case 1:
				std::cerr << negx << std::endl;
				break;
			case 2:
				std::cerr << posy << std::endl;
				break;
			case 3:
				std::cerr << negy << std::endl;
				break;
			case 4:
				std::cerr << posz << std::endl;
				break;
			case 5:
				std::cerr << negz << std::endl;
				break;
			}
			std::cerr << IMG_GetError() << std::endl;
			exit(1);
		}

		switch (testFormat(image[i]->format->format))
		{
		case RGB:
			glTexImage2D(cube_map_target[i], 0, GL_RGB8, image[i]->w, image[i]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		case BGR:
			glTexImage2D(cube_map_target[i], 0, GL_RGB8, image[i]->w, image[i]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		case RGBA:
			glTexImage2D(cube_map_target[i], 0, GL_RGBA8, image[i]->w, image[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		default:
			std::cerr << "Format " << image[i]->format->format << " unknown" << std::endl;
			break;
		}
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(image[i]);
	}
}
