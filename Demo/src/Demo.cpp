#include "Demo.hpp"

Demo::Demo(Engine::Renderer *r, Engine::Input *i, Engine::Audio *a)
{
	renderer = r;
	input = i;
	audio = a;

	gBuffer = new Engine::GBuffer;
	dMaps = new Engine::DepthMap[3];
	camera = new Engine::FreeCam(-glm::pi<GLfloat>() / 2, 0);

	octreeSystem = new Engine::OctreeSystem(4, glm::vec3(0, 0, 0), 1000);

	nightBox = new NightBox;
	tree = new Tree;
	armySoldier = new ArmySoldier;
	helicopter = new Helicopter;
	ground = new Ground;
	moonLight = new MoonLight;
	torchLight = new TorchLight;
	rainEffect = new RainEffect;
	smokeEffect = new SmokeEffect;
	textDisplay = new TextDisplay;
	screenDisplay = new ScreenDisplay;

	// GBuffer config
	gBuffer->config(renderer->getWidth(), renderer->getHeight());
	dMaps[0].config(2048, 2048);
	dMaps[1].config(2048, 2048);
	dMaps[2].config(2048, 2048);

	// Camera config
	camera->setCameraPosition(glm::vec3(30, 5, 0));

	rainEffect->init(camera->getCameraPosition(), 10000);
	smokeEffect->init(glm::vec3(-50, 0, 50), 100);

	smokeEffect->setPosition(glm::vec3(-50, 0, 50));

	// Model config
	tree->getModel()->setPosition(glm::vec3(50, 0, 50));
	tree->getModel()->setRotation(glm::vec3(-glm::pi<GLfloat>() / 2, 0, 0));
	tree->getModel()->setScale(glm::vec3(5, 5, 5));

	armySoldier->getModel()->setRotation(glm::vec3(0, 1, 0), glm::pi<GLfloat>() / 2);

	helicopter->getModel()->setPosition(glm::vec3(-50, 4, 50));
	helicopter->getModel()->setRotation(glm::vec3(-0.1f, 0, -0.5f));
    helicopter->getModel()->setScale(glm::vec3(2, 2, 2));
		
	octreeSystem->addModel(ground->getModel(), 1000);
	octreeSystem->addModel(tree->getModel(), 40);
	octreeSystem->addModel(armySoldier->getModel(), 40);
	octreeSystem->addModel(helicopter->getModel(), 40);

	torchLight->getLight()->setPosition(glm::vec3(25, 100, -25));
	torchLight->getLight()->setDirection(glm::vec3(-1.0f, -1.0f, 1.0f));
	torchLight->getLight()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torchLight->getLight()->setSpotCutOff(glm::pi<GLfloat>() / 4);
	torchLight->getLight()->setMaxDistance(250);

	// Text config
	textDisplay->getText()->writeScreen(0 + (renderer->getWidth() - (renderer->getWidth() / 10)), 0,
		renderer->getWidth() / 10, renderer->getHeight() / 10,
		renderer, "test");

	rainEffect->getSound()->setGain(0.10f);
	rainEffect->getSound()->setPitch(1.0f);
	rainEffect->getSound()->setLoop(AL_TRUE);
	rainEffect->getSound()->loadFromFile("../share/Demo/resources/sound/rain_stereo.wav", 22050, AL_FORMAT_STEREO16);

	smokeEffect->getSound()->setGain(0.75f);
	smokeEffect->getSound()->setPitch(0.75f);
	smokeEffect->getSound()->setLoop(AL_TRUE);
	smokeEffect->getSound()->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	smokeEffect->getSound()->setDistances(1.0f, 100.0f);
	smokeEffect->getSound()->loadFromFile("../share/Demo/resources/sound/fire_mono.wav", 44100, AL_FORMAT_MONO16);

	rainEffect->getSound()->play();
	smokeEffect->getSound()->play();
}

Demo::~Demo(void)
{
	delete screenDisplay;
	delete textDisplay;
	delete smokeEffect;
	delete rainEffect;
	delete moonLight;
	delete torchLight;
	delete ground;
	delete helicopter;
	delete armySoldier;
	delete tree;
	delete nightBox;

	delete octreeSystem;

	delete camera;
	delete[] dMaps;
	delete gBuffer;
}

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	static std::set<Engine::Model *> object;
	static Engine::DirLight *moon_light = moonLight->getLight();
	static Engine::SpotLight *torch_light = torchLight->getLight();
	static Engine::ParticlesManager *rain_particles = rainEffect->getParticlesManager();
	static Engine::ParticlesManager *smoke_particles = smokeEffect->getParticlesManager();
	static Engine::TextArray *text_display = textDisplay->getText();
	static Engine::Screen *screen_display = screenDisplay->getScreen();

	// We retrieve object to display from the octree
	object.clear();
	octreeSystem->getModels(gBuffer, camera, &object);

	// Clear Buffers
	renderer->clear();
	gBuffer->clear();

	nightBox->display(gBuffer, camera);

	// Opaque Object
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->display(gBuffer, camera);

	dMaps[0].clear();
	dMaps[1].clear();
	dMaps[2].clear();
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayDepthMap(dMaps, moon_light);
	moon_light->display(gBuffer, dMaps, camera);

	dMaps[0].clear();
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayDepthMap(dMaps, torch_light);
	torch_light->display(gBuffer, dMaps, camera);

	screen_display->background(gBuffer);

	// Transparent Object
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayTransparent(gBuffer, camera);
	moon_light->display(gBuffer, camera);
	torch_light->display(gBuffer, camera);

	screen_display->background(gBuffer);

	// Particles
	rain_particles->display(gBuffer, camera);
	smoke_particles->display(gBuffer, camera);

	screen_display->display(renderer, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);

	text_display->display(renderer);
}

void Demo::idle(long long time)
{
	UNREFERENCED_PARAMETER(time);

	static Engine::DirLight *moon_light = moonLight->getLight();
	static Engine::SpotLight *torch_light = torchLight->getLight();
	static Engine::ParticlesManager *rain_particles = rainEffect->getParticlesManager();
	static Engine::ParticlesManager *smoke_particles = smokeEffect->getParticlesManager();
	static glm::vec3 camPosition;
	static glm::vec3 camForward;
	static glm::vec3 camUp;

	input->refresh();
	if (input->getKeyBoardState(SDL_SCANCODE_ESCAPE))
		renderer->stopLoop();

	// Player control
	if (input->getKeyBoardState(SDL_SCANCODE_LSHIFT))
		camera->setSpeed(0.05f);
	else if (input->getMouseState(SDL_BUTTON_LEFT))
		camera->setSpeed(5.0f);
	else
		camera->setSpeed(0.25f);

	camera->keyboardMove(
		input->getKeyBoardState(SDL_SCANCODE_W),
		input->getKeyBoardState(SDL_SCANCODE_S),
		input->getKeyBoardState(SDL_SCANCODE_A),
		input->getKeyBoardState(SDL_SCANCODE_D));
	camera->mouseMove(input->getMouseRelX(), input->getMouseRelY());
	camera->position();

	camPosition = camera->getCameraPosition();
	camForward = camera->getForwardVector();
	camUp = camera->getUpVector();

	moon_light->position(camPosition, 100, 250, 500);
	torch_light->position(dMaps);

	rain_particles->setPosition(camPosition);

	rain_particles->updateParticles();
	smoke_particles->updateParticles();

	audio->setListenerPosition(camPosition, camForward, camUp);
}

void Demo::reshape(GLuint w, GLuint h)
{
	camera->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}

void Demo::launch(void)
{
	renderer->mainLoop(this);
}
