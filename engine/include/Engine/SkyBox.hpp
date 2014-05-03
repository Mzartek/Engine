#ifndef SKYBOX
#define SKYBOX

#include "ShaderProgram.hpp"
#include "Camera.hpp"

namespace engine
{
  class SkyBox
  {
  private:
    GLuint _idTexture;
    GLuint _idVAO;
    GLuint _idVBO;
    GLuint _idIBO;
    GLuint _numElement;
    Camera *_cam;
    ShaderProgram *_program;
    GLint _MVPLocation;
    GLint _textureLocation;
    GLfloat _angle, _x, _y, _z;
  public:
    SkyBox(void);
    ~SkyBox(void);
    void load(std::string posx, std::string negx,
	      std::string posy, std::string negy,
	      std::string posz, std::string negz,
	      GLfloat dim, Camera *cam, ShaderProgram *program);
    void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void display(void);
  };
}


#endif
