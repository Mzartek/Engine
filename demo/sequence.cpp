#include "mainHead.hpp"

void sequence(void)
{
	GLfloat mat1[16];
	static engine::Vector3D<GLfloat> target;
	static GLubyte step = 0; // For the demo
	static GLfloat dec = 0.0f, rotHeli = 0, rotor = 0, height = 6.0f;
	static GLfloat angleCam, distCam;
	static GLfloat angleCube = 0.0, rotCube = 0.0f;;
	static GLuint timeStart = SDL_GetTicks();

	helicopterMatrixIdentity();
	helicopterMatrixTranslate(0, height, 0);
	helicopterMatrixRotate(rotHeli, 0.0, 1.0, 0.0);

	cube1->matIdentity();
	cube1->matTranslate(0, height - 4.0f, 0);
	cube1->matRotate(angleCube, 0.0, 0.0, 1.0);
	cube1->matTranslate(-30, 0, 0);
	cube1->matRotate(rotCube, 1.0, 0.0, 0.0);
	cube1->matRotate(rotCube, 0.0, 1.0, 0.0);
	cube1->matRotate(rotCube, 0.0, 0.0, 1.0);
	
	cube2->matIdentity();
	cube2->matTranslate(0, height - 4.0f, 0);
	cube2->matRotate(angleCube, 0.0, 0.0, 1.0);
	cube2->matTranslate(+30, 0, 0);
	cube2->matRotate(rotCube, 0.0, 0.0, 1.0);
	cube2->matRotate(rotCube, 0.0, 1.0, 0.0);
	cube2->matRotate(rotCube, 1.0, 0.0, 0.0);
	
	cube3->matIdentity();
	cube3->matTranslate(0, height - 4.0f, 0);
	cube3->matRotate(angleCube, 1.0, 0.0, 0.0);
	cube3->matTranslate(0, 0, +40);
	cube3->matRotate(rotCube, 0.0, 1.0, 0.0);
	cube3->matRotate(rotCube, 1.0, 0.0, 0.0);
	cube3->matRotate(rotCube, 0.0, 0.0, 1.0);
	
	cube4->matIdentity();
	cube4->matTranslate(0, height - 4.0f, 0);
	cube4->matRotate(angleCube, 1.0, 0.0, 0.0);
	cube4->matTranslate(0, 0, -40);
	cube4->matRotate(rotCube, 0.0, 1.0, 0.0);
	cube4->matRotate(rotCube, 0.0, 0.0, 1.0);
	cube4->matRotate(rotCube, 1.0, 0.0, 0.0);

	matrixLoadIdentity(mat1);
	// sa = 0.0f;
	
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
			angleCam = 0.0f;
		}
		break;

	case 3:
		if (sa > 0.0f)
			sa -= 0.05f;
		
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 0, 1, 0);
		matrixTranslate(mat1, -10, 1, -8);

		rotor += 20.0f;
		angleCam += 0.01f;
		if ((SDL_GetTicks() - timeStart) > 27450) // Front
		{
			step++;
			angleCam = 179.0f;
		}
		break;

	case 4:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 1.0, 5.0);

		rotor += 20.0f;
		angleCam -= 0.1f;
		if ((SDL_GetTicks() - timeStart) > 35450) // Cote
		{
			step++;
			angleCam = -30.0f;
		}
		break;

	case 5:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.5, 15.0);

		rotor += 20.0f;
		angleCam -= 0.1f;
		if ((SDL_GetTicks() - timeStart) > 37450) // Front
		{
			step++;
			angleCam = 180.0f;
		}
		break;

	case 6:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 15.0);

		rotor += 20.0f;
		angleCam += 0.2f;
		if ((SDL_GetTicks() - timeStart) > 39450) // Arriere
		{
			step++;
			angleCam = -10.0f;
		}
		break;

	case 7:
		target = helicopter->getPosition();
		target._z += 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 1.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 15.0);

		rotor += 20.0f;
		angleCam += 0.2f;
		if ((SDL_GetTicks() - timeStart) > 41450) // Avancer
		{
			step++;
			angleCam = 220.0f;
			distCam = 100.0f;
		}
		break;

	case 8:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, distCam);

		rotor += 20.0f;
		distCam -= 0.6f;
		if ((SDL_GetTicks() - timeStart) > 43450) // Decollage
		{
			step++;
		}
		break;

	case 9:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 6.0f - height, distCam);

		rotor += 20.0f;
		height += dec;
		rotCube += 0.1f;
		if (dec < 0.3)
			dec += 0.01f;
		if ((SDL_GetTicks() - timeStart) > 51450) // Remise a niveau
		{
			step++;
		}
		break;

	case 10:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 0.0, 1.0, 15.0);

		rotor += 20.0f;
		height += 0.1f;
		rotCube += 0.1f;
		angleCam += 0.5f;
		if ((SDL_GetTicks() - timeStart) > 59450) // Vue du dessus
		{
			step++;
		}
		break;

	case 11:
		target = helicopter->getPosition();

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 0.0, 1.0, 0.0);
		matrixTranslate(mat1, 1.0, 10.0, 0.0);

		rotor += 20.0f;
		rotCube += 0.5f;
		angleCam += 0.5f;
		if ((SDL_GetTicks() - timeStart) > 67450) // Vue de devant
		{
			step++;
			angleCam = 200.0f;
		}
		break;

	case 12:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 20.0);

		rotor += 20.0f;
		rotCube += 0.5f;
		angleCam -= 0.01f;
		if ((SDL_GetTicks() - timeStart) > 75450) // Helico qui tourne
		{
			step++;
		}
		break;

	case 13:
		target = helicopter->getPosition();
		target._z -= 10.0f;

		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 20.0);

		rotor += 20.0f;
		rotHeli -= 0.1f;
		angleCube += 0.5f;
		rotCube += 0.5f;
		angleCam -= 0.01f;
		if ((SDL_GetTicks() - timeStart) > 102750) // Helico qui tombe
		{
			step++;
		}
		break;

	case 14:
		matrixTranslate(mat1, target._x, target._y, target._z);
		matrixRotate(mat1, angleCam, 1.0, 0.0, 0.0);
		matrixTranslate(mat1, 0.0, 0.0, 20.0);

		rotor += 20.0f;
		rotHeli -= 0.1f;
		height -= 0.5f;
		rotCube += 0.5f;
		angleCam -= 0.01f;
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
		text1->write("Ce programme");
		text2->write("vous a ete");
		text3->write("presente par:");
		if ((SDL_GetTicks() - timeStart) > 123825) // Credit 2
			step++;
		break;

	case 17:
		text1->write("Programmeur:");
		text2->write("Kevin Havranek");
		text3->write(" ");
		if ((SDL_GetTicks() - timeStart) > 132200) // Credit 3
			step++;
		break;

	case 18:
		text1->write("Musique:");
		text2->write("Jojo Beat");
		text3->write("Aka Geoffrey Richoux");
		if ((SDL_GetTicks() - timeStart) > 140575) // Credit 4
			step++;
		break;

	case 19:
		text1->write("Merci");
		text2->write("d'avoir regarde!");
		text3->write(" ");
		if ((SDL_GetTicks() - timeStart) > 148950) // Fin
			step++;
		break;

	case 20:
		window->stop();
		break;
	}

	helicopterRotateRotor(rotor);
	
	helicopterMatrixScale(2, 2, 2);
	cube1->matScale(4.0, 4.0, 4.0);
	cube2->matScale(4.0, 4.0, 4.0);
	cube3->matScale(4.0, 4.0, 4.0);
	cube4->matScale(4.0, 4.0, 4.0);

	sun->setPosition(helicopter->getPosition()._x, helicopter->getPosition()._y, helicopter->getPosition()._z);
	cam->setPositionCamera(mat1[12], mat1[13], mat1[14]);
	cam->setPositionTarget(target._x, target._y, target._z);
	
	// cam->keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
}
