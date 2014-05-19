#include "mainHead.hpp"

void sequence(void)
{
  GLfloat mat1[16];
  engine::Vector3D<GLfloat> target;
  static GLubyte step = 0;
  static GLfloat rotor = 0, height = 3, angle, dist;
  static GLuint timeStart = SDL_GetTicks();
  
  helicopterMatrixIdentity();
  helicopterMatrixScale(2, 2, 2);
  helicopterMatrixTranslate(0, height, 0);
  helicopterRotateRotor(rotor);
  
  matrixLoadIdentity(mat1);
  
  switch (step)
    {
    case 0: // 0
      sr = sg = sb = 0.0f;
      if(sa > 0.0f)
  	sa -= 0.001f;
      
      target = helicopter.getPosition();
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, -20, 0, 1, 0);
      matrixTranslate(mat1, 10, 0, 0);
      
      if((SDL_GetTicks() - timeStart)>17000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  sa = 1.0f;
  	}
      break;
      
    case 1: // 17000
      sr = sg = sb = 1.0f;
      if(sa > 0.0f)
  	sa -= 0.05f;
      
      target = helicopter.getPosition();
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixTranslate(mat1, 0, 10, -50);
  
      rotor += 1.0f;
      if((SDL_GetTicks() - timeStart)>550)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  sa = 1.0f;
  	}
      break;
      
    case 2: // 17550
      if(sa > 0.0f)
  	sa -= 0.05f;
      
      target = helicopter.getPosition();
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixTranslate(mat1, 10, 10, -20);
  
      rotor += 10.0f;
      if((SDL_GetTicks() - timeStart)>550)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  sa = 1.0f;
	  angle = 0.0f;
  	}
      break;
      
    case 3: // 18100
      if(sa > 0.0f)
  	sa -= 0.05f;
      
      target = helicopter.getPosition();
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 0, 1, 0);
      matrixTranslate(mat1, -10, 1, -8);
  
      rotor += 20.0f;
      angle += 0.01f;
      if((SDL_GetTicks() - timeStart)>10800)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  angle=179.0f;
  	}
      break;

    case 4: // 28900      
      target = helicopter.getPosition();
      target._z -= 10.0f;
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
      matrixTranslate(mat1, 0.0, 1.0, 5.0);
      
      rotor += 20.0f;
      angle -= 0.1f;
      if((SDL_GetTicks() - timeStart)>7900)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  angle = -30.0f;
  	}
      break;

    case 5:// 36800      
      target = helicopter.getPosition();
      target._z -= 10.0f;
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
      matrixTranslate(mat1, 0.0, 0.5, 15.0);
      
      rotor += 20.0f;
      angle -= 0.1f;
      if((SDL_GetTicks() - timeStart)>2000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  angle = 180.0f;
  	}
      break;

    case 6:// 38800
      target = helicopter.getPosition();
      target._z -= 10.0f;
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 1.0, 0.0, 0.0);
      matrixTranslate(mat1, 0.0, 0.0, 15.0);
      
      rotor += 20.0f;
      angle += 0.2f;
      if((SDL_GetTicks() - timeStart)>2000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  angle = -10.0f;
  	}
      break;

    case 7:// 40800
      target = helicopter.getPosition();
      target._z += 10.0f;
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 1.0, 1.0, 0.0);
      matrixTranslate(mat1, 0.0, 0.0, 15.0);
      
      rotor += 20.0f;
      angle += 0.2f;
      if((SDL_GetTicks() - timeStart)>2000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	  angle = 220.0f;
	  dist = 100.0f;
  	}
      break;

    case 8:// 42800      
      target = helicopter.getPosition();
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
      matrixTranslate(mat1, 0.0, 0.0, dist);
      
      rotor += 20.0f;
      dist -= 0.6f;
      if((SDL_GetTicks() - timeStart)>2100)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;

    case 9:// 44900
      target = helicopter.getPosition();
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
      matrixTranslate(mat1, 0.0, 0.0f - height, dist);
      
      rotor += 20.0f;
      height += 0.3f;
      if((SDL_GetTicks() - timeStart)>8100)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;

    case 10:// 53000
      target = helicopter.getPosition();
      
      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
      matrixTranslate(mat1, 0.0, 1.0, 15.0);
      
      rotor += 20.0f;
      height += 0.1f;
      angle += 0.5f;
      if((SDL_GetTicks() - timeStart)>8000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
  	}
      break;

    case 11:// 61000
      target = helicopter.getPosition();

      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
      matrixTranslate(mat1, 1.0, 10.0, 0.0);
      
      rotor += 20.0f;
      angle += 0.5f;
      if((SDL_GetTicks() - timeStart)>5000)
  	{
  	  step++;
  	  timeStart = SDL_GetTicks();
	  angle = 200.0f;
  	}
      break;

    case 12:
      target = helicopter.getPosition();
      target._z -= 10.0f;

      matrixTranslate(mat1, target._x, target._y, target._z);
      matrixRotate(mat1, angle, 1.0, 0.0, 0.0);
      matrixTranslate(mat1, 0.0, 0.0, 20.0);
      
      rotor += 20.0f;
      angle -= 0.01f;
    }
  
  sun.setPosition(helicopter.getPosition()._x, helicopter.getPosition()._y, helicopter.getPosition()._z);
  cam.setPositionCamera(mat1[12], mat1[13], mat1[14]);
  cam.setPositionTarget(target._x, target._y, target._z);
  
  // cam.keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
}
