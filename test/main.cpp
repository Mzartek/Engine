#include <cstdlib>

#include <Engine/Window.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GLcontext.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/Light.hpp>
#include <Engine/OBJModel.hpp>

#define ESC 41
#define MAJ 225

bool keyState[256];
engine::Window window;

engine::ShaderProgram *program;
engine::ShaderProgram *nolight;
engine::ShaderProgram *shadowProgram;
engine::GLcontext context1;
engine::GLcontext context2;
engine::ShadowMap shadow;

engine::FreeCam cam;
engine::Light firstLight;
engine::Model face;
engine::OBJModel helicopter;
engine::OBJModel bulb;

void display(void)
{
  firstLight.position();
  shadow.clear();
  face.displayShadow();
  helicopter.displayShadow();

  cam.position(90);
  engine::GLcontext::clear();
  face.display();
  helicopter.display();
  bulb.display();
  
  glUseProgram(0);
}

void idle(void)
{
  // static engine::Vector3D<float> lightPosition, lightDirection;

  cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  helicopter.matRotate(0.1, 0, 0, 1);
  
  // lightPosition = cam.getPositionCamera();
  // lightDirection = cam.getForward();
  // firstLight.setPosition(lightPosition._x, lightPosition._y, lightPosition._z);
  // firstLight.setDirection(lightDirection._x, lightDirection._y, lightDirection._z);
}

void reshape(int w, int h)
{
  engine::GLcontext::config(w, h, 0.1, 1200.0);
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
  GLfloat vertex[]={-100, -100, 0,
		    0, 0,//
		    0, 0, -1,
		    -100, 100, 0,
		    0, 1,//
		    0, 0, -1,
		    100, 100, 0,
		    1, 1,//
		    0, 0, -1,
		    100, -100, 0,
		    1, 0,//
		    0, 0, -1
  };
  GLuint index[]={0, 1, 2, 0, 2, 3};
  GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {20.0};

  program = new engine::ShaderProgram();
  nolight = new engine::ShaderProgram();
  shadowProgram = new engine::ShaderProgram();
  program->loadProgram("../shader/lightVert.c", "../shader/lightFrag.c");
  nolight->loadProgram("../shader/noLightVert.c", "../shader/noLightFrag.c");
  shadowProgram->loadProgram("../shader/shadowVert.c", "../shader/shadowFrag.c");
  
  engine::GLcontext::config(window.getWidth(), window.getHeight(), 0.1, 1200);
  shadow.config(1024, 1024, shadowProgram);

  context1.setShaderProgram(program);
  context2.setShaderProgram(nolight);
  
  cam.setGLcontext(&context1);
  firstLight.setGLcontext(&context1);
  face.setGLcontext(&context1);
  helicopter.setGLcontext(&context1);
  bulb.setGLcontext(&context2);

  firstLight.setShadowMap(&shadow);
  face.setShadowMap(&shadow);
  helicopter.setShadowMap(&shadow);

  firstLight.setPosition(0, 20, 0);
  firstLight.setDirection(1, -1, 1);
  firstLight.setCone(45);
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

  bulb.loadObj("resources/light_bulb/light_bulb.obj");
  bulb.matTranslate(10, 5, 10);
  bulb.matScale(0.05, 0.05, 0.05);
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
  delete nolight;
  delete shadowProgram;
  return 0;
}
