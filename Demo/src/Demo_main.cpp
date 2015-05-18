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
     for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
	  (*it)->display(gBuffer, camera);

     for (GLuint i = 0; i < CSM_NUM; i++) depthMaps[i]->clear();
     for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
	  (*it)->displayDepthMaps(depthMaps, moon_light);
     moon_light->display(gBuffer, camera, depthMaps);

     depthMaps[0]->clear();
     for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
	  (*it)->displayDepthMap(depthMaps[0], torch_light);
     torch_light->display(gBuffer, camera, depthMaps[0]);
     if (_flash) thunder_light->display(gBuffer, camera);

     screen_display->background(gBuffer);

     // Transparent Object
     for (std::set<Engine::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
	  (*it)->displayTransparent(gBuffer, camera);
     moon_light->display(gBuffer, camera);
     torch_light->display(gBuffer, camera);
     if (_flash) thunder_light->display(gBuffer, camera);

     screen_display->background(gBuffer);

     // Particles
     rain_particles->display(gBuffer, camera);
     smoke_particles->display(gBuffer, camera);

     switch (_step)
     {
     case 2:
	  explosion_particles->display(gBuffer, camera);
	  break;
     }

     screen_display->display(window, gBuffer, _screenColor);

     text_display->display(window);
}

void Demo::state(long long time)
{
     static GLfloat rotation = 0;
     static glm::mat4 movement;
     static glm::vec3 tmp[2];

     const glm::vec3 &camPosition = camera->getCameraPosition();

     this->manage_input();

     switch (_step)
     {
     case 0:
	  tmp[0] = tree_model->getPosition() + glm::vec3(0, 10, 0);

	  movement = glm::translate(tmp[0]);
	  movement *= glm::rotate(rotation, glm::vec3(0, 1, 0));
	  movement *= glm::translate(glm::vec3(30, -5, 0));
	  rotation += 0.001f;

	  camera->setPositionAndTarget(glm::vec3(movement[3]), tmp[0]);

	  if (time > 10000)
	  {
	       thunderLight->playRandomSound();
	       thunderLight->generateDirection();
	       _flash = 10;
	       _generateRandomFlash = true;
	       _step++;
	  }
	  break;

     case 1:
	  if (helicopter_model->getPosition().y > 3)
	  {
	       helicopter_model->addRotation(glm::vec3(0, 1, 0), 0.025f);
	       helicopter_model->addPosition(glm::vec3(0, -1, 0));
	  }
	  else
	  {
	       explosionEffect->init(helicopter->getModel()->getPosition() - glm::vec3(0, 5, 0), 1000);
	       explosionEffect->getSound()->play();
	       _step++;
	  }
	  break;

     case 2:
	  explosionEffect->updateParticles();

	  if (time > 32000)
	  {
	       rotation = glm::pi<GLfloat>();
	       _step++;
	  }
	  break;

     case 3:
	  tmp[0] = helicopter_model->getPosition();

	  movement = glm::translate(tmp[0]);
	  movement *= glm::rotate(rotation, glm::vec3(0, 1, 0));
	  movement *= glm::translate(glm::vec3(30, 5, 0));
	  rotation += 0.001f;

	  camera->setPositionAndTarget(glm::vec3(movement[3]), tmp[0]);

	  if (time > 60000)
	  {
	       tmp[1] = glm::vec3(movement[3]);
	       _generateRandomFlash = false;
	       _step++;
	  }
	  break;

     case 4:
	  tmp[0] += glm::vec3(0, 0.1f, 0);
	  tmp[1] += glm::vec3(0, 0.1f, 0);

	  camera->setPositionAndTarget(tmp[1], tmp[0]);

	  if (_screenColor.x > 0)	_screenColor += glm::vec4(-0.0025f, -0.0025f, -0.0025f, 0);
	  break;
     }

     rainEffect->setPosition(camPosition);
     smokeEffect->setPosition(helicopter_model->getPosition() - glm::vec3(0, 5, 0));

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
     octree->removeModel(helicopter_model.get());
     octree->addModel(helicopter_model.get(), 40);
     octree->getModels(camera, object_display);

     //RandomFlash
     if (_generateRandomFlash)
     {
	  if ((GLfloat)rand() / RAND_MAX > 0.999f)
	  {
	       thunderLight->playRandomSound();
	       thunderLight->generateDirection();
	       _flash = 10;
	  }
     }

     Engine::Audio::Instance().setListenerPosition(camPosition, camForward, camUp);
}

void Demo::reshape(GLuint w, GLuint h)
{
     camera->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}
