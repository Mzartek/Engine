#include "mainHead.hpp"

void sequence(void)
{
	GLfloat mat1[16];
	static engine::Vector3D<GLfloat> target;
	static GLubyte step = 0;
	static GLfloat angle, dist, a = 0, rotor = 0, height = 2.8f;
	static GLuint timeStart = SDL_GetTicks();

	helicopterMatrixIdentity();
	helicopterMatrixScale(2, 2, 2);
	helicopterMatrixTranslate(0, height, 0);
	helicopterMatrixRotate(a, 0.0, 1.0, 0.0);

	matrixLoadIdentity(mat1);
	sa = 0.0f;
	
	switch (step)
	{
	case 0: // Debut
		sr = sg = sb = 0.0f;
		if (sa > 0.0f)
			sa -= 0.001f;

		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, -20, 0, 1, 0);
		matrixTranslate(mat1, 10, 0, 0);

		if ((SDL_GetTicks() - timeStart) > 15450) // PAF 1
		{
			step++;
			sa = 1.0f;
		}
		break;

	case 1:
		sr = sg = sb = 1.0f;
		if (sa > 0.0f)
			sa -= 0.05f;

		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixTranslate(mat1, 0, 10, -50);

		rotor += 1.0f;
		if ((SDL_GetTicks() - timeStart) > 16200) // PAF 2
		{
			step++;
			sa = 1.0f;
		}
		break;

	case 2:
		if (sa > 0.0f)
			sa -= 0.05f;

		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixTranslate(mat1, 10, 10, -20);

		rotor += 10.0f;
		if ((SDL_GetTicks() - timeStart) > 16950) // PAF 3
		{
			step++;
			sa = 1.0f;
			angle = 0.0f;
		}
		break;

	case 3:
		if (sa > 0.0f)
			sa -= 0.05f;
		
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 0, 1, 0);
		matrixTranslate(mat1, -10, 1, -8);

		rotor += 20.0f;
		angle += 0.01f;
		if ((SDL_GetTicks() - timeStart) > 27450) // Front
		{
			step++;
			angle = 179.0f;
		}
		break;

	case 4:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 1.0, 5.0);

		rotor += 20.0f;
		angle -= 0.1f;
		if ((SDL_GetTicks() - timeStart) > 35450) // Cote
		{
			step++;
			angle = -30.0f;
		}
		break;

	case 5:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.5, 15.0);

		rotor += 20.0f;
		angle -= 0.1f;
		if ((SDL_GetTicks() - timeStart) > 37450) // Front
		{
			step++;
			angle = 180.0f;
		}
		break;

	case 6:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 15.0);

		rotor += 20.0f;
		angle += 0.2f;
		if ((SDL_GetTicks() - timeStart) > 39450) // Arriere
		{
			step++;
			angle = -10.0f;
		}
		break;

	case 7:
		target = helicopter->getPosition();
		target._z += 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 1.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 15.0);

		rotor += 20.0f;
		angle += 0.2f;
		if ((SDL_GetTicks() - timeStart) > 41450) // Avancer
		{
			step++;
			angle = 220.0f;
			dist = 100.0f;
		}
		break;

	case 8:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, dist);

		rotor += 20.0f;
		dist -= 0.6f;
		if ((SDL_GetTicks() - timeStart) > 43450) // Decollage
		{
			step++;
			a = 0.01f;
		}
		break;

	case 9:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 2.8f - height, dist);

		rotor += 20.0f;
		height += a;
		if (a < 0.3)
			a += 0.01f;
		if ((SDL_GetTicks() - timeStart) > 51450) // Remise a niveau
		{
			step++;
		}
		break;

	case 10:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 1.0, 15.0);

		rotor += 20.0f;
		height += 0.1f;
		angle += 0.5f;
		if ((SDL_GetTicks() - timeStart) > 59450) // Vue du dessus
		{
			step++;
		}
		break;

	case 11:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 1.0, 10.0, 0.0);

		rotor += 20.0f;
		angle += 0.5f;
		if ((SDL_GetTicks() - timeStart) > 67450) // Arrivee cubes
		{
			step++;
			angle = 200.0f;
		}
		break;

	case 12:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 20.0);

		rotor += 20.0f;
		angle -= 0.01f;
		if ((SDL_GetTicks() - timeStart) > 75450) // Helico qui tourne
		{
			step++;
		}
		break;

	case 13:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 20.0);

		rotor += 20.0f;
		angle -= 0.01f;
		a -= 0.1f;
		if ((SDL_GetTicks() - timeStart) > 102750) // Helico qui tombe
		{
			step++;
		}
		break;

	case 14:
		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angle, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 20.0);

		rotor += 20.0f;
		angle -= 0.01f;
		a -= 0.1f;
		height -= 0.5f;
		if ((SDL_GetTicks() - timeStart) > 106250) // Fin
		{
			step++;
			sr = sg = sb = 0.0f;
			sa = 1.0f;
		}
		break;

	case 15:
		if ((SDL_GetTicks() - timeStart) > 115450) // Credit 1
			step++;
		break;

	case 16:
		text1->write("Programmeur:");
		text2->write("Kevin Havranek");
		text3->write(" ");
		if ((SDL_GetTicks() - timeStart) > 127750) // Credit 2
			step++;
		break;

	case 17:
		text1->write("Musique:");
		text2->write("Jojo Beat");
		text3->write("Aka Geoffrey Richoux");
		if ((SDL_GetTicks() - timeStart) > 138250) // Credit 3
			step++;
		break;

	case 18:
		text1->write("Merci");
		text2->write("d'avoir regarde!");
		text3->write(" ");
		if ((SDL_GetTicks() - timeStart) > 148950) // Credit 3
			step++;
		break;

	case 19:
		window->stop();
		break;
	}

	helicopterRotateRotor(rotor);

	sun->setPosition(helicopter->getPosition()._x, helicopter->getPosition()._y, helicopter->getPosition()._z);
	// cam->setPositionCamera(mat1[12], mat1[13], mat1[14]);
	// cam->setPositionTarget(target._x, target._y, target._z);
	
	cam->keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
}
