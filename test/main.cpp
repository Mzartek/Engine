#include <Engine/Window.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GLcontext.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/OBJModel.hpp>

#define ESC 41
#define MAJ 225

bool keyState[256];
engine::Window window;

engine::ShaderProgram *program;
engine::ShaderProgram *shadowProgram;
engine::GLcontext context;

engine::FreeCam cam;
engine::DirLight firstLight;
engine::Model face;
engine::OBJModel helicopter;

void display(void)
{
  firstLight.position();
  firstLight.newLoop();
  face.displayShadow(&firstLight);
  helicopter.displayShadow(&firstLight);

  cam.position();
  context.newLoop();
  face.display();
  helicopter.display();
}

void idle(void)
{
  static engine::Vector3D<float> camPosition;

  cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  camPosition = cam.getPositionCamera();
  
  firstLight.setPosition(camPosition._x, camPosition._y, camPosition._z);
  
  helicopter.matRotate(0.1, 0, 0, 1);
}

void reshape(int w, int h)
{
  cam.setPerspective(90.0, w, h, 0.1, 1200.0);
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
  cam.setPositionCamera(0, 1, 0);
  cam.setSpeed(0.25);
}

void initGL(void)
{
  GLfloat vertex[]={-200, -200, 0,
		    0, 0,//
		    0, 0, -1,
		    -200, 200, 0,
		    0, 1,//
		    0, 0, -1,
		    200, 200, 0,
		    1, 1,//
		    0, 0, -1,
		    200, -200, 0,
		    1, 0,//
		    0, 0, -1
  };
  GLuint index[]={0, 1, 2, 0, 2, 3};
  GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {20.0};

  program = new engine::ShaderProgram();
  shadowProgram = new engine::ShaderProgram();
  program->loadProgram("../shader/demoVert.c", "../shader/demoFrag.c");
  shadowProgram->loadProgram("../shader/shadowVert.c", "../shader/shadowFrag.c");

  context.setShaderProgram(program);
  context.setCamera(&cam);
  context.setDirLight(&firstLight);
  
  face.setGLcontext(&context);
  helicopter.setGLcontext(&context);

  firstLight.configShadowMap(1024, 1024, shadowProgram);
  firstLight.setDirection(0, -1, 1);
  firstLight.setAmbient(mat_ambient[0], mat_ambient[1], mat_ambient[2], mat_ambient[3]);
  firstLight.setDiffuse(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2], mat_diffuse[3]);
  firstLight.setSpecular(mat_specular[0], mat_specular[1], mat_specular[2], mat_specular[3]);
  
  face.createObject(sizeof vertex, vertex,
  		    sizeof index, index,
  		    "./resources/bleu.jpg",
  		    mat_ambient, mat_diffuse, mat_specular, mat_shininess);
  face.matRotate(90, 1, 0, 0);

  helicopter.loadObj("resources/UH-60_Blackhawk/uh60.obj");
  helicopter.matTranslate(15, 10, 15);
  helicopter.matRotate(-90, 1, 0, 0);
  helicopter.matScale(2, 2, 2);
}

int main(int argc, char **argv)
{
  init();
  
  if(argc < 3)
    window.initWindow("Demo", 800, 600);
  else
    window.initWindow("Demo", atoi(argv[1]), atoi(argv[2]));
  window.setDisplayFunc(display);
  window.setIdleFunc(idle);
  window.setReshapeFunc(reshape);
  window.setKeyboardFunc(keyboard);
  window.setMouseMoveFunc(mouseMove);
  
  initGL();

  window.mainLoop();

  delete program;
  delete shadowProgram;
  return 0;
}
