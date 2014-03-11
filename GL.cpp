#include "include/Engine/GL.hpp"

void engine::loadTexBMP(char const *path, GLuint *texture)
{
  SDL_Surface *image = IMG_Load(path);
  if(image==NULL)
    {
      std::cerr << "Error while loading image" << std::endl;
      exit(1);
    }

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image->w, image->h, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
}

void engine::loadTexPNG_RGB(char const *path, GLuint *texture)
{
  SDL_Surface *image = IMG_Load(path);
  if(image==NULL)
    {
      std::cerr << "Error while loading image" << std::endl;
      exit(1);
    }

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image->w, image->h, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
}

void engine::loadTexPNG_RGBA(char const *path, GLuint *texture)
{
  SDL_Surface *image = IMG_Load(path);
  if(image==NULL)
    {
      std::cerr << "Error while loading image" << std::endl;
      exit(1);
    }

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image->w, image->h, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
}

void engine::initBufferObject(GLuint type, int size, GLuint *id, GLvoid *data)
{
  glGenBuffers(1, id);

  glBindBuffer(type, *id);
  glBufferData(type, size, data, GL_STATIC_DRAW);
  
  glBindBuffer(type, 0);
}

char* engine::readText(const char* filename)
{
  std::ifstream file(filename, std::ifstream::in);
  char* content = NULL;
  unsigned long size;

  //On obtient la taille du fichier
  file.seekg(0, std::ifstream::end);
  size = file.tellg();
  file.seekg(0, std::ifstream::beg);

  //On remplit content
  content = new char[size+1];
  if(content == NULL)
    {
      std::cerr << "Error in the allocation for file: " << filename << std::endl;
      exit(1);
    }
  file.read(content, size);
  content[size] = '\0';
  
  return content;
}
