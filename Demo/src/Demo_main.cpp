#include "Demo.hpp"

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	if (_flash) _flash--;

	// Clear Buffers
	window->clear();
	gBuffer->clear();

	nightBox->display(gBuffer, camera);

	// Opaque Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->display(gBuffer, camera);

	for (GLuint i = 0; i < Graphics::DirLight::CASCADED_LEVEL; i++) depthMaps[i]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMaps(depthMaps, moon_light);
	moon_light->display(gBuffer, camera, depthMaps);

	depthMaps[0]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMap(depthMaps[0], torch_light);
	torch_light->display(gBuffer, camera, depthMaps[0]);
	if (_flash) thunder_light->display(gBuffer, camera);

	screen_display->background(gBuffer);

	// Transparent Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayTransparent(gBuffer, camera);
	moon_light->display(gBuffer, camera);
	//torch_light->display(gBuffer, camera);
	if (_flash) thunder_light->display(gBuffer, camera);

	screen_display->background(gBuffer);

	// Particles
	rain_particles->display(gBuffer, camera);
	smoke_particles->display(gBuffer, camera);

	if (_step == 0 || _step == 1)	for (GLuint i = 0; i < 8; i++) if (_displayFireflies[i]) 
			fireflies_particles[i]->display(gBuffer, camera);
	if (_step == 2) explosion_particles->display(gBuffer, camera);

	screen_display->display(window, gBuffer, _screenColor);

	if (_displayCredits) text_display->display(window);
}

void Demo::state(long long time)
{
	static GLfloat rotation = glm::pi<GLfloat>() / 1.25f;
	static GLfloat rotFireflies[] = { 0, glm::pi<GLfloat>(), glm::pi<GLfloat>() / 2, (glm::pi<GLfloat>() * 2) - (glm::pi<GLfloat>() / 2) };
	static glm::mat4 movement;
	static glm::mat4 movFireflies[8];
	static glm::vec3 tmp[2];
	static GLfloat velocity, music_volume = 1.0f;
	static long long saveTime = 0;
	static long long nextTime = saveTime + 87000;

	const glm::vec3 &camPosition = camera->getCameraPosition();

	this->manage_input();

	switch (_step)
	{
	case 0:
		tmp[0] = tree_model->getPosition() + glm::vec3(0, 15, 0);
		tmp[1] = tree_model->getPosition() + glm::vec3(0, 25, 0);

		movement  = glm::translate(tmp[0]);
		movement *= glm::rotate(rotation, glm::vec3(0, 1, 0));
		movement *= glm::translate(glm::vec3(30, -5, 0));
		rotation += 0.002f;

    camera->setPositionAndTarget(glm::vec3(movement[3]), tmp[0]);
		rainEffect->getSound()->setGain((GLfloat)time / nextTime / 10);

		for (GLuint i = 0; i < 8; i++)
		{
		}

		if (time > 16000)
		{
				movFireflies[0] = glm::translate(tmp[1]);
				movFireflies[0] *= glm::rotate(rotFireflies[0], glm::vec3(0, 1, 0));
				movFireflies[0] *= glm::translate(glm::vec3(15, -5, 0));
				rotFireflies[0] -= 0.01f;

				firefliesEffects[0]->setPosition(glm::vec3(movFireflies[0][3]));
				firefliesEffects[0]->updateParticles();

				_displayFireflies[0] = true;
		}
		if (time > 26000)
		{
				movFireflies[1] = glm::translate(tmp[1]);
				movFireflies[1] *= glm::rotate(rotFireflies[1], glm::vec3(0, 1, 0));
				movFireflies[1] *= glm::translate(glm::vec3(15, -5, 0));
				rotFireflies[1] -= 0.01f;

				firefliesEffects[1]->setPosition(glm::vec3(movFireflies[1][3]));
				firefliesEffects[1]->updateParticles();

				_displayFireflies[1] = true;
		}
		if (time > 36000)
		{
				movFireflies[2] = glm::translate(tmp[1]);
				movFireflies[2] *= glm::rotate(rotFireflies[2], glm::vec3(0, 1, 0));
				movFireflies[2] *= glm::translate(glm::vec3(15, -5, 0));
				rotFireflies[2] -= 0.01f;

				firefliesEffects[2]->setPosition(glm::vec3(movFireflies[2][3]));
				firefliesEffects[2]->updateParticles();

				_displayFireflies[2] = true;
		}
		if (time > 46000)
		{
				movFireflies[3] = glm::translate(tmp[1]);
				movFireflies[3] *= glm::rotate(rotFireflies[3], glm::vec3(0, 1, 0));
				movFireflies[3] *= glm::translate(glm::vec3(15, -5, 0));
				rotFireflies[3] -= 0.01f;

				firefliesEffects[3]->setPosition(glm::vec3(movFireflies[3][3]));
				firefliesEffects[3]->updateParticles();

				_displayFireflies[3] = true;
		}
		if (time > 56000)
		{
				movFireflies[4] = glm::translate(tmp[1]);
				movFireflies[4] *= glm::translate(glm::vec3(15, -5, 15));

				firefliesEffects[4]->setPosition(glm::vec3(movFireflies[4][3]));
				firefliesEffects[4]->updateParticles();

				_displayFireflies[4] = true;
		}
		if (time > 66000)
		{
				movFireflies[5] = glm::translate(tmp[1]);
				movFireflies[5] *= glm::translate(glm::vec3(15, -5, -15));

				firefliesEffects[5]->setPosition(glm::vec3(movFireflies[5][3]));
				firefliesEffects[5]->updateParticles();

				_displayFireflies[5] = true;
		}
		if (time > 76000)
		{
				movFireflies[6] = glm::translate(tmp[1]);
				movFireflies[6] *= glm::translate(glm::vec3(-15, -5, 15));

				firefliesEffects[6]->setPosition(glm::vec3(movFireflies[6][3]));
				firefliesEffects[6]->updateParticles();

				_displayFireflies[6] = true;
		}
		if (time > 86000)
		{
				movFireflies[7] = glm::translate(tmp[1]);
				movFireflies[7] *= glm::translate(glm::vec3(-15, -5, -15));

				firefliesEffects[7]->setPosition(glm::vec3(movFireflies[7][3]));
				firefliesEffects[7]->updateParticles();

				_displayFireflies[7] = true;
		}

		if (_screenColor.x < 1.0) _screenColor += glm::vec4(0.0025f, 0.0025f, 0.0025f, 0);

		if (time > nextTime)
		{
			thunderLight->playRandomSound();
			_flash = 25;
			_generateRandomFlash = true;

			_step++;
		}
		break;

	case 1:
		if (helicoptercorps_model->getPosition().y > 3)
		{
			helicopter->addRotation(glm::vec3(0, 1, 0), 0.1f);
			helicopter->addPosition(glm::vec3(0, -1, 0));

			for (GLuint i = 0; i < 8; i++)
			{
					movFireflies[i] *= glm::translate(glm::vec3(-5, 0, 0));

					firefliesEffects[i]->setPosition(glm::vec3(movFireflies[i][3]));
					firefliesEffects[i]->updateParticles();
			}
		}
		else
		{
			helicopter->setMount(false);
			explosionEffect->init(helicoptercorps_model->getPosition() - glm::vec3(0, 5, 0), 1000);
			explosionEffect->getSound()->play();
			rotation = glm::pi<GLfloat>() / 4;
			velocity = 1.0f;

			_step++;
			saveTime = time;
			nextTime = saveTime + 7000;
		}
		break;

	case 2:
		explosionEffect->updateParticles();

		if (helicoptergrotor_model->getPosition().x < tree_model->getPosition().x)
		{
			helicoptergrotor_model->addPosition(glm::vec3(1.0f, 0.0f, 0.0));
			helicoptergrotor_model->addRotation(glm::vec3(0, 1, 0), velocity);
		}
		else if (rotation > 0.0f)
		{
			helicoptergrotor_model->addPosition(glm::vec3(0.25f, -0.025f, -0.25f));
			helicoptergrotor_model->addRotation(glm::vec3(0, 1, 0), velocity);
			if (velocity > 0.0f) velocity -= 0.02f;

			tree_model->addRotation(glm::vec3(-1, 0, 1), -0.025f);
			rotation -= 0.025f;
		}
		else if (helicoptergrotor_model->getPosition().y > 4.0f)
		{
			helicoptergrotor_model->addPosition(glm::vec3(0.25f, -0.025f, -0.25f));
			helicoptergrotor_model->addRotation(glm::vec3(0, 1, 0), velocity);
			if (velocity > 0.0f) velocity -= 0.025f;
		}

		if (time > nextTime)
		{
			rotation = glm::pi<GLfloat>();

			_step++;
			saveTime = time;
			nextTime = saveTime + 10000;
		}
		break;

	case 3:
		tmp[0] = helicoptercorps_model->getPosition();

		movement  = glm::translate(tmp[0]);
		movement *= glm::rotate(rotation, glm::vec3(0, 1, 0));
		movement *= glm::translate(glm::vec3(30, 5, 0));
		rotation += 0.001f;

		camera->setPositionAndTarget(glm::vec3(movement[3]), tmp[0]);

		if (time > nextTime)
		{
			tmp[1] = glm::vec3(movement[3]);
			_generateRandomFlash = false;

			_step++;
			saveTime = time;
			nextTime = saveTime + 25000;
		}
		break;

	case 4:
		tmp[0] += glm::vec3(0, 0.1f, 0);
		tmp[1] += glm::vec3(0, 0.1f, 0);

		camera->setPositionAndTarget(tmp[1], tmp[0]);

		if (_screenColor.x > 0) _screenColor += glm::vec4(-0.0025f, -0.0025f, -0.0025f, 0);
		if (music_volume > 0)
		{
			music->setGain(music_volume);
			music_volume -= 0.001f;
		}
		else
		{
			_displayCredits = true;
		}

		if (time > nextTime) window->stopLoop();
		break;
	}

	torch_light->setPosition(helicoptercorps_model->getPosition() + glm::vec3(0, 100, -100));

	rainEffect->setPosition(camPosition);
	smokeEffect->setPosition(helicoptercorps_model->getPosition() - glm::vec3(0, 5, 0));

	rainEffect->updateParticles();
	smokeEffect->updateParticles();
}

void Demo::last_state(void)
{
	const glm::vec3 &camPosition = camera->getCameraPosition();
	const glm::vec3 &camForward = camera->getForwardVector();
	const glm::vec3 &camUp = camera->getUpVector();

	camera->updateData();
	moon_light->updateData(camPosition, 100, 250, 500);
	torch_light->updateData(depthMaps[0]);

	// We retrieve object to display from the octree
	object_display.clear();

	if (_step > 0)
	{
		octree->removeModel(helicoptercorps_model.get());
		octree->removeModel(helicoptergrotor_model.get());

		octree->addModel(helicoptercorps_model.get(), 40);
		octree->addModel(helicoptergrotor_model.get(), 40);
	}

	octree->getModels(camera, object_display);

	//RandomFlash
	if (_generateRandomFlash)
	{
		if ((GLfloat)rand() / RAND_MAX > 0.999f)
		{
			thunderLight->playRandomSound();
			_flash = 25;
		}
	}
	if (_flash) thunderLight->generateDirection();

	Audio::AudioRenderer::Instance().setListenerPosition(camPosition, camForward, camUp);
}

void Demo::reshape(GLuint w, GLuint h)
{
	camera->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}
