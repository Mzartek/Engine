#include <Engine/Window.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/OBJModel.hpp>
#include <Engine/SkyBox.hpp>
#include <SDL2/SDL_mixer.h>

#define ESC 41
#define MAJ 225

bool keyState[256];
Mix_Music *song;

engine::Window window;
engine::Renderer renderer;
engine::ShaderProgram *mainProgram;
engine::ShaderProgram *shadowProgram;
engine::ShaderProgram *skyboxProgram;

engine::FreeCam cam;
engine::DirLight sun;
engine::Model face;
engine::OBJModel helicopter;
engine::SkyBox sky;

void display(void)
{
  sun.position();
  sun.newLoop();
  face.displayShadow(&sun);
  helicopter.displayShadow(&sun);

  cam.position();
  renderer.newLoop();
  sky.display();
  face.display();
  helicopter.display();
}

void idle(void)
{
  static engine::Vector3D<float> camPosition;

  cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  camPosition = cam.getPositionCamera();
  
  sun.setPosition(camPosition._x, camPosition._y, camPosition._z);
  
  helicopter.matRotate(0.1, 0, 0, 1);
}

void reshape(GLuint w, GLuint h)
{
  cam.setPerspective(90.0, w, h, 0.1, 1500.0);
}

void keyboard(GLubyte key, GLboolean state)
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

void mouseMove(GLint xrel, GLint yrel)
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

  mainProgram = new engine::ShaderProgram();
  shadowProgram = new engine::ShaderProgram();
  skyboxProgram = new engine::ShaderProgram();
  mainProgram->loadProgram("shader/demoVert.c", "shader/demoFrag.c");
  shadowProgram->loadProgram("shader/shadowVert.c", "shader/shadowFrag.c");
  skyboxProgram->loadProgram("shader/skyboxVert.c", "shader/skyboxFrag.c");

  renderer.setShaderProgram(mainProgram);
  renderer.setCamera(&cam);
  renderer.setDirLight(&sun);

  sky.load("resources/sand.jpg", "resources/sand.jpg",
	   "resources/sand.jpg", "resources/sand.jpg",
	   "resources/sand.jpg", "resources/sand.jpg", 
  	   100, &cam, skyboxProgram);
  face.setRenderer(&renderer);
  helicopter.setRenderer(&renderer);
  
  face.createObject(sizeof vertex, vertex,
  		    sizeof index, index,
  		    "./resources/sand.jpg",
  		    mat_ambient, mat_diffuse, mat_specular, mat_shininess);
  face.matRotate(90, 1, 0, 0);

  helicopter.loadObj("resources/UH-60_Blackhawk/uh60.obj");
  helicopter.sortObject();
  helicopter.matScale(2, 2, 2);
  helicopter.matTranslate(15, 10, 15);
  helicopter.matRotate(-90, 1, 0, 0);

  sun.configShadowMap(2048, 2048, shadowProgram);
  sun.setDirection(0, -1, 1);
  sun.setAmbient(mat_ambient[0], mat_ambient[1], mat_ambient[2], mat_ambient[3]);
  sun.setDiffuse(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2], mat_diffuse[3]);
  sun.setSpecular(mat_specular[0], mat_specular[1], mat_specular[2], mat_specular[3]);
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
  
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    std::cerr << Mix_GetError() << std::endl;
  song = Mix_LoadMUS("resources/song/song.mp3");
  Mix_PlayMusic(song, -1);
  Mix_VolumeMusic(MIX_MAX_VOLUME/2);

  window.mainLoop();

  Mix_FreeMusic(song);
  Mix_CloseAudio();
  
  delete mainProgram;
  delete shadowProgram;
  delete skyboxProgram;
  
  return 0;
}
