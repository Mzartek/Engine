#include <Engine/Window.hpp>
#include <Engine/OBJModel.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GLcontext.hpp>
#include <Engine/Light.hpp>

#define ESC 41
#define MAJ 225

bool keyState[256];
engine::Window window;
engine::GLcontext context;
engine::FreeCam cam;
engine::Light firstLight;
engine::Model face;
engine::OBJModel firstObj;
engine::ShaderProgram *program;


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  cam.position();
  firstLight.position();
  
  firstObj.display();

  face.display();
  
  glUseProgram(0);
}

void idle(void)
{
  // static engine::Vector3D<float> lightPosition;
  
  cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  // lightPosition = cam.getPositionCamera();
  // firstLight.setPosition(lightPosition._x, lightPosition._y, lightPosition._z);
}

void reshape(int w, int h)
{
  context.adjust(w, h, 90.0, 0.1, 1200.0);
}

void keyboard(unsigned char key, bool state)
{
  keyState[key] = state;
  
  if(keyState[MAJ]==true)
    cam.setSpeed(0.05);
  else
    cam.setSpeed(0.25);
  
  if(state)
    switch(key)
      {
      case ESC:
	window.stop();
	break;
      }
}

void mouseMove(int xrel, int yrel)
{
  cam.mouseMove(xrel, yrel);
}

void init(void)
{
  cam.setSpeed(0.25);
}

void initGL(void)
{
  GLfloat vertex[]={-5, -5, 0,
		    0.25, 0.25,//
		    0, 0, -1,
		    -5, 5, 0,
		    0.25, 0.75,//
		    0, 0, -1,
		    5, 5, 0,
		    0.75, 0.75,//
		    0, 0, -1,
		    5, -5, 0,
		    0.75, 0.25,//
		    0, 0, -1
  };
  GLuint index[]={0, 1, 2, 0, 2, 3};
  GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {2.0};

  program = new engine::ShaderProgram();
  program->loadProgram("../shader/minimal.vert", "../shader/minimal.frag");
  
  context.setShaderProgram(program);
  cam.setShaderProgram(program);
  firstLight.setShaderProgram(program);
  face.setShaderProgram(program);
  firstObj.setShaderProgram(program);

  firstLight.setPosition(-5, 10, 0);
  firstLight.setAmbient(mat_ambient[0], mat_ambient[1], mat_ambient[2], mat_ambient[3]);
  firstLight.setDiffuse(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2], mat_diffuse[3]);
  firstLight.setSpecular(mat_specular[0], mat_specular[1], mat_specular[2], mat_specular[3]);
  
  face.createObject(vertex, sizeof vertex,
		    index, sizeof index,
		    "./resources/cav.png",
		    mat_ambient, mat_diffuse, mat_specular, mat_shininess);
  face.matTranslate(0, 10, 5);
  face.matRotate(90, 0, 1, 0);

  firstObj.loadObj("resources/UH-60 Blackhawk/uh60.obj");
  firstObj.matTranslate(10, 10, 10);
  firstObj.matRotate(-90, 1, 0, 0);
  firstObj.matScale(2, 2, 2);
}

int main(int argc, char **argv)
{
  init();
  
  window.initWindow("GLSL", 800, 600);
  window.setDisplayFunc(display);
  window.setIdleFunc(idle);
  window.setReshapeFunc(reshape);
  window.setKeyboardFunc(keyboard);
  window.setMouseMoveFunc(mouseMove);
  
  initGL();

  window.mainLoop();

  delete program;
  return 0;
}
