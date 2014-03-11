#include <Engine/Window.hpp>
#include <Engine/Object.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/ShaderProgram.hpp>

#define ESC 41

bool keyState[256];
engine::FreeCam cam;
engine::Window window;
engine::Object cube;
engine::ShaderObject *test1;
engine::ShaderObject *test2;
engine::ShaderProgram *program;

void display(void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  gluLookAt(cam.getCamera()._x, cam.getCamera()._y, cam.getCamera()._z,
  	    cam.getTarget()._x, cam.getTarget()._y, cam.getTarget()._z,
  	    0, 1, 0);

  cube.display();
}

void idle(void)
{
  cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  cam.genTarget();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (GLdouble)w/(GLdouble)h, 0.1, 1200);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, bool state)
{
  keyState[key] = state;
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
  cam.genTarget();
}

void init(void)
{
  cam.setPosition(0, 0, 0);
  cam.setSpeed(1);
}

void initGL(void)
{
  unsigned id;
  GLfloat vertex[]={0, 0, 0,
		    0, 0, 0,//
		    0, 0, -1,
		    0, 10, 0,
		    0, 1, 0,//
		    0, 0, -1,
		    10, 10, 0,
		    1, 1, 0,//
		    0, 0, -1,
		    10, 0, 0,
		    1, 0, 0,//
		    0, 0, -1
  };
  GLuint index[]={0, 1, 2, 3};
  
  engine::initBufferObject(GL_ARRAY_BUFFER, sizeof vertex, &id, vertex);
  cube.setIdObject(id);
  engine::initBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof index, &id, index);
  cube.setIdElementObject(id, sizeof vertex/sizeof *vertex);
  //engine::loadTexPNG_RGB("./resources/roi.png", &id);
  engine::loadTexBMP("./resources/bleu.bmp", &id);
  cube.setIdTextureObject(id);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_SMOOTH);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  test1 = new engine::ShaderObject();
  test2 = new engine::ShaderObject();
  program = new engine::ShaderProgram();
  test1->loadShader("minimal.vert", GL_VERTEX_SHADER);
  test2->loadShader("minimal.frag", GL_FRAGMENT_SHADER);
  program->attachShader(test1);
  program->attachShader(test2);
  program->link();
  program->use();
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
  delete test1;
  delete test2;
  return 0;
}
