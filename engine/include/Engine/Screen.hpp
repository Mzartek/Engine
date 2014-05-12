#ifndef SCREEN
#define SCREEN

#include "ShaderProgram.hpp"

namespace engine
{
  class Screen
  {
  private:
    GLuint _idVAO;
    GLuint _idVBO;
    ShaderProgram *_program;
    GLint _colorLocation;
  public:
    Screen();
    ~Screen();
    void init(ShaderProgram *program);
    void display(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
  };
}

#endif
