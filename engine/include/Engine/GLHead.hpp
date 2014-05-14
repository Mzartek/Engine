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
#include "matrix.hpp"

namespace engine
{
  enum pixelFormat {UNKNOWN, RGB, BGR, RGBA};
  extern DLLAPI pixelFormat testFormat(unsigned f);
  extern DLLAPI void loadTex(const std::string path, GLuint *texture);
}

#endif
