#include <Engine/GLHead.hpp>

engine::pixelFormat engine::testFormat(GLuint f)
{
	switch(f)
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

void engine::loadTextureFromFile(const std::string path, GLuint *texture)
{
	SDL_Surface *image = IMG_Load(&path[0]);
	if(image==NULL)
	{
		std::cerr << "Error while loading image: " << path << std::endl;
		exit(1);
	}

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	switch(testFormat(image->format->format))
	{
	case RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case BGR:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		break;
	default:
		std::cerr << "Format " << image->format->format << " unknown" << std::endl;
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(image);
}

void engine::loadTextureFromSDL_Surface(const SDL_Surface *image, GLuint *texture)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	switch(testFormat(image->format->format))
	{
	case RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case BGR:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
		break;
	case RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		break;
	default:
		std::cerr << "Format " << image->format->format << " unknown" << std::endl;
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
