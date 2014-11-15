#include "config.hpp"

void GameManager::display(GLfloat state)
{
    GLuint i;

    renderer->clear();
    gBuffer->clear();
    torch->clear();

    // Skybox
    skybox->display(gBuffer, player->getCamera());

    // Shadow Map
    for (i = 0; i < vector_cepe->size(); i++)
        (*vector_cepe)[i]->displayShadowMap(torch);

    for (i = 0; i < vector_phalloide->size(); i++)
        (*vector_phalloide)[i]->displayShadowMap(torch);

    for (i = 0; i < vector_satan->size(); i++)
        (*vector_satan)[i]->displayShadowMap(torch);

    // Opaque Object
    sol->display(gBuffer, player->getCamera());

    for (i = 0; i < vector_cepe->size(); i++)
        (*vector_cepe)[i]->display(gBuffer, player->getCamera());

    for (i = 0; i < vector_phalloide->size(); i++)
        (*vector_phalloide)[i]->display(gBuffer, player->getCamera());

    for (i = 0; i < vector_satan->size(); i++)
        (*vector_satan)[i]->display(gBuffer, player->getCamera());

    torch->display(gBuffer, player->getCamera());
    screen->background(gBuffer);

    // Transparent Object
    sol->displayTransparent(gBuffer, player->getCamera());
    torch->display(gBuffer, player->getCamera());
    screen->background(gBuffer);

    if (player->isAlive())
        screen->display(renderer, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);
    else
        screen->display(renderer, gBuffer, 1.0f, 0.5f, 0.5f, 1.0f);

    text->display(renderer);
}

void GameManager::idle(void)
{
    GLuint i;

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

        torch->setPosition(player->getCamera()->getPositionCamera() - glm::vec3(0.0f, 1.0f, 0.0f));
        torch->setDirection(player->getCamera()->getForward());

        player->getCamera()->position();
        torch->position();
    }

    // Mushroom manager
    for (i = 0; i < vector_cepe->size(); i++)
    {
        if (glm::length(player->getCamera()->getPositionCamera() - (*vector_cepe)[i]->getPosition()) < 5)
        {
            player->eatMushroom((*vector_cepe)[i]);
            delete (*vector_cepe)[i];
            vector_cepe->erase(vector_cepe->begin() + i);
            text->writeScreen(std::to_string(player->getLife()).c_str());
        }
    }

    for (i = 0; i < vector_phalloide->size(); i++)
    {
        if (glm::length(player->getCamera()->getPositionCamera() - (*vector_phalloide)[i]->getPosition()) < 5)
        {
            player->eatMushroom((*vector_phalloide)[i]);
            delete (*vector_phalloide)[i];
            vector_phalloide->erase(vector_phalloide->begin() + i);
            text->writeScreen(std::to_string(player->getLife()).c_str());
        }
    }

    for (i = 0; i < vector_satan->size(); i++)
    {
        if (glm::length(player->getCamera()->getPositionCamera() - (*vector_satan)[i]->getPosition()) < 5)
        {
            player->eatMushroom((*vector_satan)[i]);
            delete (*vector_satan)[i];
            vector_satan->erase(vector_satan->begin() + i);
            text->writeScreen(std::to_string(player->getLife()).c_str());
        }
    }
}

void GameManager::reshape(GLuint w, GLuint h)
{
    player->getCamera()->setPerspective(90.0f, w, h, 0.1f, 1000.0f);
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
