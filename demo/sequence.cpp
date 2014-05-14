#include "mainHead.hpp"

void sequence(void)
{
  GLfloat mat1[16];
  static GLubyte step = 0;
  static GLfloat rotor = 0, height = 3.0;
  static GLuint timeStart = SDL_GetTicks();
  
  helicopterMatrixIdentity();
  helicopterMatrixScale(2, 2, 2);
  
  switch (step)
    {
    case 0: //Position static pour 17 secondes
      sr = sg = sb = 0.0;
      if(sa > 0.0f)
	sa -= 0.001f;
      
      helicopterMatrixTranslate(0, height, 0);
      
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixRotate(mat1, -20, 0, 1, 0);
      matrixTranslate(mat1, 10, 0, 0);
      
      if((SDL_GetTicks() - timeStart)>17000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
	  sa = 1.0;
  	}
      break;
      
    case 1: // PAF 1
      sr = sg = sb = 1.0;
      if(sa > 0.0f)
	sa -= 0.05f;

      helicopterMatrixTranslate(0, height, 0);
      
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixTranslate(mat1, 0, 10, -50);
  
      rotor += 1.0;
      if((SDL_GetTicks() - timeStart)>580)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
	  sa = 1.0;
  	}
      break;
      
    case 2: // PAF 2
      if(sa > 0.0f)
	sa -= 0.05f;

      helicopterMatrixTranslate(0, height, 0);
      
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixTranslate(mat1, 10, 10, -20);
  
      rotor += 10.0;
      if((SDL_GetTicks() - timeStart)>580)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
	  sa = 1.0;
  	}
      break;
      
    case 3: // PAF 3
      if(sa > 0.0f)
	sa -= 0.05f;

      helicopterMatrixTranslate(0, height, 0);
      
      matrixLoadIdentity(mat1);
      matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
      matrixTranslate(mat1, -10, 1, -8);
  
      rotor += 20.0;
      if((SDL_GetTicks() - timeStart)>200000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;
    }

  /*
    case 2:
    helicopterMatrixTranslate(0, height, 0);
      
    matrixLoadIdentity(mat1);
    matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
    matrixRotate(mat1, angle, 0, 1, 0);
    matrixTranslate(mat1, 40, 10-height, 0);
      
    angle -=0.5;
    height += 0.25;
    if((SDL_GetTicks() - timeStart)>6000)
    {
    step++;
    timeStart = SDL_GetTicks();
    }
    break;

    case 3:
    helicopterMatrixTranslate(0, height, 0);
      
    matrixLoadIdentity(mat1);
    matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
    matrixRotate(mat1, angle, 0, 1, 0);
    matrixTranslate(mat1, 40, 10, 0);
      
    angle +=0.5;
    height += 0.25;
    if((SDL_GetTicks() - timeStart)>11000)
    {
    step++;
    timeStart = SDL_GetTicks();
    }
    break;

    case 4:
    helicopterMatrixTranslate(0, height, 0);
      
    matrixLoadIdentity(mat1);
    matrixTranslate(mat1, helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
    matrixRotate(mat1, angle, 0, 1, 0);
    matrixTranslate(mat1, 20, 10, 0);
      
    angle -=0.5;
    if((SDL_GetTicks() - timeStart)>11000)
    {
    step++;
    timeStart = SDL_GetTicks();
    }
    break;
      
    case 5:
    window.stop();
    break;
    }*/
  
  helicopterMatrixRotate(-90, 1, 0, 0);
  helicopterRotateRotor(rotor);
  
  sun.setPosition(helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
  cam.setPositionCamera(mat1[12], mat1[13], mat1[14]);
  cam.setPositionTarget(helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
  
  // cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
  // helicopter.matRotate(0.1, 0, 0, 1);
}
