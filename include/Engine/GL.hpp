#ifndef GL_PERSO
#define GL_PERSO

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <cassert>
#include <cctype>
#include <cmath>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine
{
  extern GLuint loadTex(const std::string path);
}

#endif
