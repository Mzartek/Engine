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

engine::Camera cam;
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
  GLfloat mat1[16];
  static GLbyte step = 0;
  static GLfloat angle = 125, height = 10;
  static GLuint timeStart = SDL_GetTicks();

  switch (step)
    {
    case 0:
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixRotate(mat1, angle, 0, 1, 0);
      matrixTranslate(mat1, 20, 10-height, 0);
      
      helicopter.matIdentity();
      helicopter.matScale(2, 2, 2);
      helicopter.matTranslate(0, height, 0);
      helicopter.matRotate(-90, 1, 0, 0);
  
      angle -= 0.9;
      if((SDL_GetTicks() - timeStart)>11000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;
    case 1:
      helicopter.matIdentity();
      helicopter.matScale(2, 2, 2);
      helicopter.matTranslate(0, height, 0);
      helicopter.matRotate(-90, 1, 0, 0);
      
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixRotate(mat1, angle, 0, 1, 0);
      matrixTranslate(mat1, 40, 10-height, 0);
      
      angle -=0.9;
      height += 0.5;
      if((SDL_GetTicks() - timeStart)>6000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;
    case 2:
      helicopter.matIdentity();
      helicopter.matScale(2, 2, 2);
      helicopter.matTranslate(0, height, 0);
      helicopter.matRotate(-90, 1, 0, 0);
      
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixRotate(mat1, angle, 0, 1, 0);
      matrixTranslate(mat1, 40, 10, 0);
      
      angle -=0.9;
      height += 0.5;
      if((SDL_GetTicks() - timeStart)>11000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;

    case 3:
      helicopter.matIdentity();
      helicopter.matScale(2, 2, 2);
      helicopter.matTranslate(0, height, 0);
      helicopter.matRotate(-90, 1, 0, 0);
      
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixRotate(mat1, angle, 0, 1, 0);
      matrixTranslate(mat1, 20, 10, 0);
      
      angle -=0.9;
      if((SDL_GetTicks() - timeStart)>11000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;
    case 4:
      window.stop();
      break;
    }
  
  sun.setPosition(helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
  cam.setPositionCamera(mat1[12], mat1[13], mat1[14]);
  cam.setPositionTarget(helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
  
  // cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  // helicopter.matRotate(0.1, 0, 0, 1);
}

void reshape(GLuint w, GLuint h)
{
  cam.setPerspective(90.0, w, h, 0.1, 1500.0);
}

void keyboard(GLubyte key, GLboolean state)
{
  keyState[key] = state;
  
  // if(keyState[MAJ]==true)
  //   cam.setSpeed(0.05);
  // else
  //   cam.setSpeed(0.25);
  
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
  (void)xrel; (void)yrel;
  // cam.mouseMove(xrel, yrel);
}

void init(void)
{
  // cam.setPositionCamera(0, 1, 0);
  // cam.setSpeed(0.25);
}

void initGL(void)
{
  GLfloat vertex[]={-1000, -1000, 0,
		    0, 0,//
		    0, 0, -1,
		    -1000, 1000, 0,
		    0, 1,//
		    0, 0, -1,
		    1000, 1000, 0,
		    1, 1,//
		    0, 0, -1,
		    1000, -1000, 0,
		    1, 0,//
		    0, 0, -1
  };
  GLuint index[]={0, 1, 2, 0, 2, 3};
  GLfloat mat_ambient[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
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

  sun.configShadowMap(2048, 2048, shadowProgram);
  sun.setDirection(1, -1, 0);
  sun.setDimension(50, 50, 50);
  sun.setAmbient(mat_ambient[0], mat_ambient[1], mat_ambient[2], mat_ambient[3]);
  sun.setDiffuse(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2], mat_diffuse[3]);
  sun.setSpecular(mat_specular[0], mat_specular[1], mat_specular[2], mat_specular[3]);

  sky.load("resources/Skybox/rightred2.jpg", "resources/Skybox/leftred2.jpg",
	   "resources/Skybox/topred2.jpg", "resources/Skybox/botred2.jpg",
	   "resources/Skybox/frontred2.jpg", "resources/Skybox/backred2.jpg",
  	   100, &cam, skyboxProgram);
  sky.rotate(0, 0, 0, 0);
  
  face.setRenderer(&renderer);
  face.createObject(sizeof vertex, vertex,
  		    sizeof index, index,
  		    "./resources/sand.jpg",
  		    mat_ambient, mat_diffuse, mat_specular, mat_shininess);
  face.matRotate(90, 1, 0, 0);

  helicopter.setRenderer(&renderer);
  helicopter.loadObj("resources/UH-60_Blackhawk/corps.obj", 1);
  helicopter.sortObject();
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
