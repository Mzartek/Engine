#include "config.hpp"

void GameManager::display(GLfloat state)
{
	renderer->clear();
	gBuffer->clear();
	sun->clear();
	torch->clear();

	// Skybox
	skybox->display(gBuffer, cam);

	// Shadow Map
	sol->displayShadowMap(sun);
	heli->displayShadowMap(sun);
	sol->displayShadowMap(torch);
	heli->displayShadowMap(torch);

	// Opaque Object
	sol->display(gBuffer, cam);
	heli->display(gBuffer, cam);
	sun->display(gBuffer, cam);
	torch->display(gBuffer, cam);
	screen->background(gBuffer);

	// Transparent Object
	sol->displayTransparent(gBuffer, cam);
	heli->displayTransparent(gBuffer, cam);
	sun->display(gBuffer, cam);
	torch->display(gBuffer, cam);
	screen->background(gBuffer);

	screen->display(renderer, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);

	text->display(renderer);
}

void GameManager::idle(void)
{
	input->refresh();
	if (input->getKeyBoardState(SDL_SCANCODE_ESCAPE))
		renderer->stopLoop();
	cam->keyboardMove(input->getKeyBoardState(SDL_SCANCODE_W), input->getKeyBoardState(SDL_SCANCODE_S), input->getKeyBoardState(SDL_SCANCODE_A), input->getKeyBoardState(SDL_SCANCODE_D));
	cam->mouseMove(input->getMouseRelX(), input->getMouseRelY());
	if (input->getKeyBoardState(SDL_SCANCODE_LSHIFT))
		cam->setSpeed(0.05f);
	else
		cam->setSpeed(0.5f);

	if (input->getMouseState(SDL_BUTTON_LEFT))
		cam->setSpeed(5.0f);

	heli->matRotate(0.1f, 0, 1, 0);

	cam->position();
	sun->position(heli->getPosition(), 25);
	torch->position();
}

void GameManager::reshape(GLuint w, GLuint h)
{
	cam->setPerspective(90.0f, w, h, 0.1f, 1000.0f);
}

void GameManager::launch(void)
{
	renderer->mainLoop(this);
}

int main(int argc, char *argv[])
{
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
