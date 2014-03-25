#ifndef GL_PERSO
#define GL_PERSO

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine
{
  extern void loadTex(const std::string path, GLuint *texture);
  extern void initBufferObject(GLuint type, GLuint size, GLuint *id, GLvoid *data);
}

#endif
