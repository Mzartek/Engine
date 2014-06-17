#ifndef GL_HEAD
#define GL_HEAD

#ifdef WIN32
#ifdef ENGINE_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <GL/glew.h>
#else
#define DLLAPI
#define GL_GLEXT_PROTOTYPES
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <math.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "matrix.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"
#include "Vector4D.hpp"

namespace engine
{
	typedef struct Vertex
	{
		Vector3D<GLfloat> position;
		Vector2D<GLfloat> texCoord;
		Vector3D<GLfloat> normal;
	} Vertex;

	enum pixelFormat {UNKNOWN, RGB, BGR, RGBA};
	extern DLLAPI pixelFormat testFormat(GLuint f);
	extern DLLAPI void loadTextureFromFile(const std::string path, GLuint *texture);
	extern DLLAPI void loadTextureFromSDL_Surface(const SDL_Surface *image, GLuint *texture);
}

#endif
