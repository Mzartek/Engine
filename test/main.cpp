#include <Engine/Window.hpp>
#include <Engine/Model.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GLcontext.hpp>

#define ESC 41

bool keyState[256];
engine::FreeCam cam;
engine::Window window;
engine::GLcontext context;
engine::Model face;
engine::Model firstObj;
engine::ShaderProgram *program;


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  cam.position();
  
  firstObj.display();
  
  // face.display();
  
  glUseProgram(0);
}

void idle(void)
{
  cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  cam.genTarget();
}

void reshape(int w, int h)
{
  context.adjust(w, h, 90.0, 0.1, 1200.0);
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
  GLfloat mat_ambiant[] = {0.2, 0.2, 0.2, 0.0};
  GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 0.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat mat_shininess[] = {2.0};

  program = new engine::ShaderProgram();
  program->loadProgram("minimal.vert", "minimal.frag");
  
  context.setProjectionMatrixLocation(program, "projectionMatrix");
  cam.setViewMatrixLocation(program, "viewMatrix");
  face.setModelMatrixLocation(program, "modelMatrix");
  firstObj.setModelMatrixLocation(program, "modelMatrix");

  face.createObject(vertex, sizeof vertex,
		    index, sizeof index,
		    "./resources/roi.png",
		    mat_ambiant, mat_diffuse, mat_specular, mat_shininess);
  // face.matTranslate(5, 5, -60);
  // face.matRotate(75, 0, 0, 1);

  firstObj.loadObj("resources/L200-OBJ/L200-OBJ.obj");
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
