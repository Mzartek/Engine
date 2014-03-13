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
engine::ShaderObject *vertexShader;
engine::ShaderObject *fragmentShader;
engine::ShaderProgram *program;


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  cam.position();

  face.display();
  
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
  cam.setPosition(0, 0, 0);
  cam.setSpeed(1);
}

void initGL(void)
{
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

  vertexShader = new engine::ShaderObject();
  fragmentShader = new engine::ShaderObject();
  program = new engine::ShaderProgram();
  
  vertexShader->loadShader("minimal.vert", GL_VERTEX_SHADER);
  fragmentShader->loadShader("minimal.frag", GL_FRAGMENT_SHADER);
  program->attachShader(vertexShader);
  program->attachShader(fragmentShader);
  program->link();
  
  context.setProjectionMatrixLocation(program, "projectionMatrix");
  cam.setViewMatrixLocation(program, "viewMatrix");
  face.setModelMatrixLocation(program, "modelMatrix");

  face.createObject(vertex, sizeof vertex,
		    index, sizeof index,
		    "./resources/bleu.bmp");
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
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
  delete vertexShader;
  delete fragmentShader;
  return 0;
}
