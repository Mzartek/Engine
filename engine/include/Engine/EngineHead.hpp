#ifndef ENGINE_HEAD
#define ENGINE_HEAD

#ifdef WIN32
#ifdef ENGINE_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#ifdef GCC
#define ALIGN(X) __attribute__((aligned(X)))
#else
#define ALIGN(X) __declspec(align(X))
#pragma warning(disable:4324)
#endif
#include <GL/glew.h>
#else
#define ALIGN(X) __attribute__((aligned(X)))
#define DLLAPI
#define GL_GLEXT_PROTOTYPES
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
	typedef struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
		glm::vec3 tangent;
	} Vertex;

	enum pixelFormat {UNKNOWN, RGB, BGR, RGBA};
	extern DLLAPI pixelFormat testFormat(const GLuint &f);
	extern DLLAPI void loadTextureFromFile(const GLchar *path, GLuint *texture);
	extern DLLAPI void loadTextureFromSDL_Surface(const SDL_Surface *image, GLuint *texture);
}

#endif
