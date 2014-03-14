#ifndef GL_PERSO
#define GL_PERSO

#include <iostream>
#include <fstream>
#include <cassert>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine
{
  extern void loadTex(char const *path, GLuint *texture);
  extern void initBufferObject(GLuint type, GLuint size, GLuint *id, GLvoid *data);
  extern char* readText(char const *filename);
}

#endif
