#include "Demo.hpp"

Demo::Demo(const std::shared_ptr<Engine::Window> &w)
	: window(w)
{
	Engine::Renderer::Instance().setGLContext(window);

	gBuffer = std::shared_ptr<Engine::GBuffer>(new Engine::GBuffer);
	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps.push_back(std::shared_ptr<Engine::DepthMap>(new Engine::DepthMap));
	camera = std::shared_ptr<Engine::PerspCamera>(new Engine::PerspCamera);

	octree = std::shared_ptr<Engine::Octree>(new Engine::Octree(4, glm::vec3(0, 0, 0), 1000));

	nightBox = std::shared_ptr<NightBox>(new NightBox);
	tree = std::shared_ptr<Tree>(new Tree);
	//animModel = std::shared_ptr<AnimModel>(new AnimModel);
	helicopter = std::shared_ptr<Helicopter>(new Helicopter);
	ground = std::shared_ptr<Ground>(new Ground);
	moonLight = std::shared_ptr<MoonLight>(new MoonLight);
	thunderLight = std::shared_ptr<ThunderLight>(new ThunderLight);
	torchLight = std::shared_ptr<TorchLight>(new TorchLight);
	rainEffect = std::shared_ptr<RainEffect>(new RainEffect);
	smokeEffect = std::shared_ptr<SmokeEffect>(new SmokeEffect);
	explosionEffect = std::shared_ptr<ExplosionEffect>(new ExplosionEffect);
	textDisplay = std::shared_ptr<TextDisplay>(new TextDisplay);
	screenDisplay = std::shared_ptr<ScreenDisplay>(new ScreenDisplay);

	// GBuffer config
	gBuffer->config(window->getWidth(), window->getHeight());
	for (GLuint i = 0; i < CSM_NUM; i++) depthMaps[i]->config(2048, 2048);

	// Camera config
	camera->setPositionAndTarget(glm::vec3(30, 5, 0), glm::vec3(50, 10, 50));

	// Model config
	tree->getModel()->setPosition(glm::vec3(50, -5, 50));
	tree->getModel()->setRotation(glm::vec3(-glm::pi<GLfloat>() / 2, 0, 0));
	tree->getModel()->setScale(glm::vec3(5, 5, 5));

	//animModel->getModel()->setPosition(glm::vec3(-25, 0, 25));
	//animModel->getModel()->setRotation(glm::vec3(0, 1, 0), glm::pi<GLfloat>() / 2);

	helicopter->setPosition(glm::vec3(-50, 304, 50));
	helicopter->setRotation(glm::vec3(-0.1f, 0, -0.5f));
	helicopter->setScale(glm::vec3(2, 2, 2));

	rainEffect->init(camera->getCameraPosition(), 10000);
	smokeEffect->init(helicopter->getCorpsModel()->getPosition(), 1000);

	octree->addModel(ground->getModel().get(), 1000);
	octree->addModel(tree->getModel().get(), 40);
	//octree->addModel(animModel->getModel().get(), 40);
	octree->addModel(helicopter->getCorpsModel().get(), 40);
	octree->addModel(helicopter->getRotorModel().get(), 40);

	torchLight->getLight()->setPosition(helicopter->getCorpsModel()->getPosition() + glm::vec3(0, 100, -100));
	torchLight->getLight()->setDirection(glm::vec3(0.0f, -1.0f, 0.5f));
	torchLight->getLight()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torchLight->getLight()->setSpotCutOff(glm::pi<GLfloat>() / 4);
	torchLight->getLight()->setMaxDistance(250);

	// Text config
	textDisplay->getText()->writeScreen(0 + (window->getWidth() - (window->getWidth() / 10)), 0,
		window->getWidth() / 10, window->getHeight() / 10,
		window, "test");

	rainEffect->getSound()->play();
	smokeEffect->getSound()->play();

	_step = 0;
	_flash = 0;
	_generateRandomFlash = false;
	_screenColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	moon_light = moonLight->getLight();
	thunder_light = thunderLight->getLight();
	torch_light = torchLight->getLight();
	rain_particles = rainEffect->getParticlesManager();
	smoke_particles = smokeEffect->getParticlesManager();
	explosion_particles = explosionEffect->getParticlesManager();
	text_display = textDisplay->getText();
	screen_display = screenDisplay->getScreen();
	helicoptercorps_model = helicopter->getCorpsModel();
	helicoptergrotor_model = helicopter->getRotorModel();
	tree_model = tree->getModel();
}

Demo::~Demo(void)
{
}
