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
  extern void loadTexBMP(char const *path, GLuint *texture);
  extern void loadTexPNG_RGB(char const *path, GLuint *texture);
  extern void loadTexPNG_RGBA(char const *path, GLuint *texture);
  extern void initBufferObject(GLuint type, int size, GLuint *id, GLvoid *data);
  extern char* readText(const char* filename);
}

#endif
