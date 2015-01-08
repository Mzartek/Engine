#include "config.hpp"

void GameManager::display(GLfloat state)
{
	GLuint i;
	static std::vector<Engine::Model *> object;

	// We retrieve object to display from the octree
	object.clear();
	octreeSystem->getModel(gBuffer, player->getCamera(), &object);

	renderer->clear();
	gBuffer->clear();
	moon->clear();
	torch->clear();

	// Skybox
	skybox->display(gBuffer, player->getCamera());

	// ShadowMap
	model_tree->displayShadowMap(moon);
	model_tree->displayShadowMap(torch);

	// Opaque Object
	for (i = 0; i < object.size(); i++)
		object[i]->display(gBuffer, player->getCamera());

	moon->display(gBuffer, player->getCamera());
	torch->display(gBuffer, player->getCamera());
	screen->background(gBuffer);

	// Transparent Object	
	/*for (i = 0; i < object.size(); i++)
		object[i]->displayTransparent(gBuffer, player->getCamera());

	moon->display(gBuffer, player->getCamera());
	torch->display(gBuffer, player->getCamera());
	screen->background(gBuffer);*/

	// Particles
	rainManager->display(gBuffer, player->getCamera());
	smokeManager->display(gBuffer, player->getCamera());

	if (player->isAlive())
		screen->display(renderer, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);
	else
		screen->display(renderer, gBuffer, 1.0f, 0.5f, 0.5f, 1.0f);

	text->display(renderer);
}

void GameManager::idle(void)
{
	GLuint i;
	glm::vec3 camPosition = player->getCamera()->getCameraPosition();

	input->refresh();
	if (input->getKeyBoardState(SDL_SCANCODE_ESCAPE))
		renderer->stopLoop();

	// Player control
	if (player->isAlive())
	{
		if (input->getKeyBoardState(SDL_SCANCODE_LSHIFT)) player->getCamera()->setSpeed(0.05f);
		else player->getCamera()->setSpeed(0.25f);
		if (input->getMouseState(SDL_BUTTON_LEFT)) player->getCamera()->setSpeed(5.0f);
		player->getCamera()->keyboardMove(input->getKeyBoardState(SDL_SCANCODE_W), input->getKeyBoardState(SDL_SCANCODE_S), input->getKeyBoardState(SDL_SCANCODE_A), input->getKeyBoardState(SDL_SCANCODE_D));
		player->getCamera()->mouseMove(input->getMouseRelX(), input->getMouseRelY());

		torch->setPosition(player->getCamera()->getCameraPosition());// - glm::vec3(0.0f, 1.0f, 0.0f));
		torch->setDirection(player->getCamera()->getForwardVector());

		rainManager->updateParticles();
		smokeManager->updateParticles();

		player->getCamera()->position();
		moon->position(glm::vec3(0, 0, 0), 100);
		torch->position();
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

int main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));

	Engine::Renderer *renderer = new Engine::Renderer("Demo OpenGL", 800, 600, GL_FALSE);
	Engine::Input *input = new Engine::Input;
	GameManager *game = new GameManager(renderer, input);

	game->launch();

	delete game;
	delete input;
	delete renderer;

	std::cout << "MemState " << Engine::Object::getMemoryState() << std::endl;
	Engine::Object::saveMemoryInfo("memLost.txt");

	return 0;
}
