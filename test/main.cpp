#include <Engine/Window.hpp>
#include <Engine/Object.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GLcontext.hpp>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ESC 41

bool keyState[256];
engine::FreeCam cam;
engine::Window window;
engine::GLcontext context;
engine::Object face;
engine::ShaderObject *matrix;
engine::ShaderObject *test;
engine::ShaderProgram *program;
glm::mat4 modelMatrix;


void display(void)
{
  static GLint modelMatrixLocation = glGetUniformLocation(program->getId(), "modelMatrix");
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  cam.position();
  
  modelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(10.0, 0.0, 0.0));
  modelMatrix = glm::rotate(modelMatrix, 48.0f, glm::vec3(0.0, 1.0, 0.0));
  program->use();
  glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

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

  matrix = new engine::ShaderObject();
  test = new engine::ShaderObject();
  program = new engine::ShaderProgram();
  matrix->loadShader("minimal.vert", GL_VERTEX_SHADER);
  test->loadShader("minimal.frag", GL_FRAGMENT_SHADER);
  program->attachShader(matrix);
  program->attachShader(test);
  program->link();
  context.setProjectionMatrixLocation(program, "projectionMatrix");
  cam.setViewMatrixLocation(program, "viewMatrix");
  
  engine::initBufferObject(GL_ARRAY_BUFFER, sizeof vertex, &id, vertex);
  face.setIdObject(id);
  engine::initBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof index, &id, index);
  face.setIdElementObject(id, sizeof vertex/sizeof *vertex);
  engine::loadTexBMP("./resources/bleu.bmp", &id);
  face.setIdTextureObject(id);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_SMOOTH);
  
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
  delete matrix;
  delete test;
  return 0;
}
