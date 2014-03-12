#include <Engine/Window.hpp>
#include <Engine/Object.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/ShaderProgram.hpp>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ESC 41

bool keyState[256];
engine::FreeCam cam;
engine::Window window;
engine::Object cube;
engine::ShaderObject *matrix;
engine::ShaderObject *test;
engine::ShaderProgram *program;
glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;
glm::mat4 modelMatrix;


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
  viewMatrix = glm::lookAt(glm::vec3((float)cam.getCamera()._x, (float)cam.getCamera()._y, (float)cam.getCamera()._z),
  			   glm::vec3((float)cam.getTarget()._x, (float)cam.getTarget()._y, (float)cam.getTarget()._z),
  			   glm::vec3(0.0f, 1.0f, 0.0f));
  modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  program->use();
  
  GLint projectionMatrixLocation = glGetUniformLocation(matrix->getId(), "projectionMatrix");
  GLint viewMatrixLocation = glGetUniformLocation(matrix->getId(), "viewMatrix");
  GLint modelMatrixLocation = glGetUniformLocation(matrix->getId(), "modelMatrix");
  
  glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
  glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
  glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

  cube.display();
  
  glUseProgram(0);
}

void idle(void)
{
  cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  cam.genTarget();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  projectionMatrix = glm::perspective(90.0f, (float)w / (float)h, 0.1f, 1200.0f);
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
  engine::loadTexBMP("./resources/bleu.bmp", &id);
  cube.setIdTextureObject(id);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_SMOOTH);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  matrix = new engine::ShaderObject();
  test = new engine::ShaderObject();
  program = new engine::ShaderProgram();
  matrix->loadShader("minimal.vert", GL_VERTEX_SHADER);
  test->loadShader("minimal.frag", GL_FRAGMENT_SHADER);
  program->attachShader(matrix);
  program->attachShader(test);
  program->link();
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
