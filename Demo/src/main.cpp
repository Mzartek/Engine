#include "config.hpp"

void GameManager::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	static std::set<Engine::Model *> object;
	static Engine::PlayerCam *player_cam = player->getCamera();

	// We retrieve object to display from the octree
	object.clear();
	octreeSystem->getModels(gBuffer, player_cam, &object);

	// Clear Buffers
	renderer->clear();
	gBuffer->clear();
	moon->clear();
	torch->clear();

	// Skybox
	skybox->display(gBuffer, player_cam);

	// ShadowMap
	model_tree->displayShadowMap(moon);
	model_tree->displayShadowMap(torch);

	// Opaque Object
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->display(gBuffer, player_cam);

	moon->display(gBuffer, player_cam);
	torch->display(gBuffer, player_cam);
	screen->background(gBuffer);

	// Transparent Object
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayTransparent(gBuffer, player->getCamera());

	moon->display(gBuffer, player->getCamera());
	torch->display(gBuffer, player->getCamera());
	screen->background(gBuffer);

	// Particles
	rainManager->display(gBuffer, player_cam);
	smokeManager->display(gBuffer, player_cam);

	if (player->isAlive())
		screen->display(renderer, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);
	else
		screen->display(renderer, gBuffer, 1.0f, 0.5f, 0.5f, 1.0f);

	text->display(renderer);
}

void GameManager::idle(void)
{
	static GLuint i;
	static Engine::PlayerCam *player_cam = player->getCamera();
	glm::vec3 camPosition;
	glm::vec3 camView;

	input->refresh();
	if (input->getKeyBoardState(SDL_SCANCODE_ESCAPE))
		renderer->stopLoop();

	// Player control
	if (player->isAlive())
	{
		if (input->getKeyBoardState(SDL_SCANCODE_LSHIFT))
			player->getCamera()->setSpeed(0.05f);
		else if (input->getMouseState(SDL_BUTTON_LEFT))
			player->getCamera()->setSpeed(5.0f);
		else
			player->getCamera()->setSpeed(0.25f);		

		player_cam->keyboardMove(
			input->getKeyBoardState(SDL_SCANCODE_W), 
			input->getKeyBoardState(SDL_SCANCODE_S), 
			input->getKeyBoardState(SDL_SCANCODE_A), 
			input->getKeyBoardState(SDL_SCANCODE_D));
		player_cam->mouseMove(input->getMouseRelX(), input->getMouseRelY());

		player_cam->position();
		camPosition = player_cam->getCameraPosition();
		camView = player_cam->getViewVector();

		moon->position(camPosition, 100, 250, 500);
		torch->position();

		rainManager->setPosition(camPosition);
		rainManager->updateParticles();
		smokeManager->updateParticles();

		audio->setListenerPosition(camPosition, camView);
	}

	// Mushroom manager
	for (i = 0; i < vector_cepe->size(); i++)
	{
		if (glm::length(camPosition - (*vector_cepe)[i]->getPosition()) < 5)
		{
			player->eatMushroom((*vector_cepe)[i]);
			octreeSystem->removeModel((*vector_cepe)[i]);
			delete (*vector_cepe)[i];
			vector_cepe->erase(vector_cepe->begin() + i);
			text->writeScreen(std::to_string(player->getLife()).c_str());
		}
	}

	for (i = 0; i < vector_phalloide->size(); i++)
	{
		if (glm::length(camPosition - (*vector_phalloide)[i]->getPosition()) < 5)
		{
			player->eatMushroom((*vector_phalloide)[i]);
			octreeSystem->removeModel((*vector_phalloide)[i]);
			delete (*vector_phalloide)[i];
			vector_phalloide->erase(vector_phalloide->begin() + i);
			text->writeScreen(std::to_string(player->getLife()).c_str());
		}
	}

	for (i = 0; i < vector_satan->size(); i++)
	{
		if (glm::length(camPosition - (*vector_satan)[i]->getPosition()) < 5)
		{
			player->eatMushroom((*vector_satan)[i]);
			octreeSystem->removeModel((*vector_satan)[i]);
			delete (*vector_satan)[i];
			vector_satan->erase(vector_satan->begin() + i);
			text->writeScreen(std::to_string(player->getLife()).c_str());
		}
	}
}

void GameManager::reshape(GLuint w, GLuint h)
{
	player->getCamera()->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}

void GameManager::launch(void)
{
	renderer->mainLoop(this);
}

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	srand((unsigned int)time(NULL));

	Engine::Renderer *renderer = new Engine::Renderer("Demo OpenGL", 800, 600, GL_FALSE);
	Engine::Audio *audio = new Engine::Audio;
	Engine::Input *input = new Engine::Input;

	GameManager *game = new GameManager(renderer, input, audio);
	
	game->launch();

	delete game;

	delete input;
	delete audio;
	delete renderer;

	std::cout << "MemState " << Engine::Object::getMemoryState() << std::endl;

	return 0;
}
