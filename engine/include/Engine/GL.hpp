#ifndef GL_PERSO
#define GL_PERSO

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <cassert>
#include <cctype>
#include <cmath>
#include <cstring>

#ifdef WIN
#include <GL/glew.h>
#else
#define GL_GLEXT_PROTOTYPES
#endif
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine
{
  extern GLuint loadTex(const std::string path);
}

#endif
