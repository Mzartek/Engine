#include "Demo.hpp"

Demo::Demo(const std::shared_ptr<Engine::Window> &w)
	: window(w)
{
	Engine::Renderer::Instance().setGLContext(window);

	gBuffer = std::shared_ptr<Engine::GBuffer>(new Engine::GBuffer);
	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps.push_back(std::shared_ptr<Engine::DepthMap>(new Engine::DepthMap));
	camera = std::shared_ptr<Engine::FreeCam>(new Engine::FreeCam(-glm::pi<GLfloat>() / 2, 0));

	octree = std::shared_ptr<Engine::Octree>(new Engine::Octree(4, glm::vec3(0, 0, 0), 1000));

	nightBox = std::shared_ptr<NightBox>(new NightBox);
	tree = std::shared_ptr<Tree>(new Tree);
	armySoldier = std::shared_ptr<ArmySoldier>(new ArmySoldier);
	helicopter = std::shared_ptr<Helicopter>(new Helicopter);
	ground = std::shared_ptr<Ground>(new Ground);
	moonLight = std::shared_ptr<MoonLight>(new MoonLight);
	torchLight = std::shared_ptr<TorchLight>(new TorchLight);
	rainEffect = std::shared_ptr<RainEffect>(new RainEffect);
	smokeEffect = std::shared_ptr<SmokeEffect>(new SmokeEffect);
	textDisplay = std::shared_ptr<TextDisplay>(new TextDisplay);
	screenDisplay = std::shared_ptr<ScreenDisplay>(new ScreenDisplay);

	// GBuffer config
	gBuffer->config(window->getWidth(), window->getHeight());
	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps[i]->config(2048, 2048);

	// Camera config
	camera->setCameraPosition(glm::vec3(30, 5, 0));

	rainEffect->init(camera->getCameraPosition(), 10000);
	smokeEffect->init(glm::vec3(-50, 0, 50), 100);

	smokeEffect->setPosition(glm::vec3(-50, 0, 50));

	// Model config
	tree->getModel()->setPosition(glm::vec3(50, 0, 50));
	tree->getModel()->setRotation(glm::vec3(-glm::pi<GLfloat>() / 2, 0, 0));
	tree->getModel()->setScale(glm::vec3(5, 5, 5));

	armySoldier->getModel()->setPosition(glm::vec3(-25, 0, 25));
	armySoldier->getModel()->setRotation(glm::vec3(0, 1, 0), glm::pi<GLfloat>() / 2);

	helicopter->getModel()->setPosition(glm::vec3(-50, 4, 50));
	helicopter->getModel()->setRotation(glm::vec3(-0.1f, 0, -0.5f));
	helicopter->getModel()->setScale(glm::vec3(2, 2, 2));
		
	octree->addModel(ground->getModel(), 1000);
	octree->addModel(tree->getModel(), 40);
	octree->addModel(armySoldier->getModel(), 40);
	octree->addModel(helicopter->getModel(), 40);

	torchLight->getLight()->setPosition(glm::vec3(25, 100, -25));
	torchLight->getLight()->setDirection(glm::vec3(-1.0f, -1.0f, 1.0f));
	torchLight->getLight()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torchLight->getLight()->setSpotCutOff(glm::pi<GLfloat>() / 4);
	torchLight->getLight()->setMaxDistance(250);

	// Text config
	textDisplay->getText()->writeScreen(0 + (window->getWidth() - (window->getWidth() / 10)), 0,
		window->getWidth() / 10, window->getHeight() / 10,
		window, "test");

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
}

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	static std::set<std::shared_ptr<Engine::Model>> object;
	static const std::shared_ptr<Engine::DirLight> moon_light = moonLight->getLight();
	static const std::shared_ptr<Engine::SpotLight> torch_light = torchLight->getLight();
	static const std::shared_ptr<Engine::ParticlesManager> rain_particles = rainEffect->getParticlesManager();
	static const std::shared_ptr<Engine::ParticlesManager> smoke_particles = smokeEffect->getParticlesManager();
	static const std::shared_ptr<Engine::TextArray> text_display = textDisplay->getText();
	static const std::shared_ptr<Engine::Screen> screen_display = screenDisplay->getScreen();

	// We retrieve object to display from the octree
	object.clear();
	octree->getModels(camera, object);

	// Clear Buffers
	window->clear();
	gBuffer->clear();

	nightBox->display(gBuffer, camera);

	// Opaque Object
	for (std::set<std::shared_ptr<Engine::Model>>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->display(gBuffer, camera);

	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps[i]->clear();
	for (std::set<std::shared_ptr<Engine::Model>>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayDepthMaps(depthMaps, moon_light);
	moon_light->display(gBuffer, camera, depthMaps);

	depthMaps[0]->clear();
	for (std::set<std::shared_ptr<Engine::Model>>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayDepthMap(depthMaps[0], torch_light);
	torch_light->display(gBuffer, camera, depthMaps[0]);

	screen_display->background(gBuffer);

	// Transparent Object
	for (std::set<std::shared_ptr<Engine::Model>>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayTransparent(gBuffer, camera);
	moon_light->display(gBuffer, camera);
	torch_light->display(gBuffer, camera);

	screen_display->background(gBuffer);

	// Particles
	rain_particles->display(gBuffer, camera);
	smoke_particles->display(gBuffer, camera);

	screen_display->display(window, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);

	text_display->display(window);
}

void Demo::idle(long long time)
{
	UNREFERENCED_PARAMETER(time);

	static const std::shared_ptr<Engine::DirLight> moon_light = moonLight->getLight();
	static const std::shared_ptr<Engine::SpotLight> torch_light = torchLight->getLight();
	static const std::shared_ptr<Engine::ParticlesManager> rain_particles = rainEffect->getParticlesManager();
	static const std::shared_ptr<Engine::ParticlesManager> smoke_particles = smokeEffect->getParticlesManager();
	static const glm::vec3 &camPosition = camera->getCameraPosition();
	static const glm::vec3 &camForward = camera->getForwardVector();
	static const glm::vec3 &camUp = camera->getUpVector();
	
	Engine::Input::Instance().refresh();
	if (Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_ESCAPE))
		window->stopLoop();

	// Player control
	if (Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_LSHIFT))
		camera->setSpeed(0.05f);
	else if (Engine::Input::Instance().getMouseState(SDL_BUTTON_LEFT))
		camera->setSpeed(5.0f);
	else
		camera->setSpeed(0.25f);

	camera->keyboardMove(
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_W),
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_S),
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_A),
		Engine::Input::Instance().getKeyBoardState(SDL_SCANCODE_D));
	camera->mouseMove(Engine::Input::Instance().getMouseRelX(), Engine::Input::Instance().getMouseRelY());
	camera->position();
	
	moon_light->position(camPosition, 100, 250, 500);
	torch_light->position(depthMaps[0]);

	rain_particles->setPosition(camPosition);

	rain_particles->updateParticles();
	smoke_particles->updateParticles();

	Engine::Audio::Instance().setListenerPosition(camPosition, camForward, camUp);
}

void Demo::reshape(GLuint w, GLuint h)
{
	camera->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}
