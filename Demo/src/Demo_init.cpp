#include "Demo.hpp"

Demo::Demo(const std::shared_ptr<Graphics::Window> &w)
		:	graphicsRenderer(Graphics::GraphicsRenderer::Instance()),
		audioRenderer(Audio::AudioRenderer::Instance()),
		inputManager(Input::InputManager::Instance()),
		window(w)
{
		graphicsRenderer.setGLContext(window);

		gBuffer = std::shared_ptr<Graphics::GBuffer>(new Graphics::GBuffer);
		camera = std::shared_ptr<Graphics::FreeCam>(new Graphics::FreeCam);

		octree = std::shared_ptr<Graphics::Octree>(new Graphics::Octree(4, glm::vec3(0, 0, 0), 1000));

		nightBox = std::shared_ptr<NightBox>(new NightBox);
		tree = std::shared_ptr<Tree>(new Tree);
		animModel = std::shared_ptr<AnimModel>(new AnimModel);
		ground = std::shared_ptr<Ground>(new Ground);
		moonLight = std::shared_ptr<MoonLight>(new MoonLight);
		torchLight = std::shared_ptr<TorchLight>(new TorchLight);
		rainEffect = std::shared_ptr<RainEffect>(new RainEffect);
		smokeEffect = std::shared_ptr<SmokeEffect>(new SmokeEffect);
		screenDisplay = std::shared_ptr<ScreenDisplay>(new ScreenDisplay);

		for (GLuint i = 0; i < Graphics::DirLight::CASCADED_LEVEL; i++) depthMaps.push_back(std::shared_ptr<Graphics::DepthMap>(new Graphics::DepthMap));

		// GBuffer config
		gBuffer->config(window->getWidth(), window->getHeight());

		// Camera config
		camera->setPositionAndTarget(glm::vec3(30, 5, 0), glm::vec3(50, 10, 50));

		// Model config
		tree->getModel()->setPosition(glm::vec3(50, -5, 50));
		tree->getModel()->setRotation(glm::vec3(-glm::pi<GLfloat>() / 2, 0, 0));
		tree->getModel()->setScale(glm::vec3(5, 5, 5));

		animModel->getModel()->setPosition(glm::vec3(-25, 0, 25));
		animModel->getModel()->setRotation(glm::vec3(0, 1, 0), glm::pi<GLfloat>() / 2);

		rainEffect->init(camera->getCameraPosition(), 10000);
		smokeEffect->init(glm::vec3(-50, 0, 50), 1000);

		octree->addModel(ground->getModel().get(), 1000);
		octree->addModel(tree->getModel().get(), 40);
		octree->addModel(animModel->getModel().get(), 40);

		torchLight->getLight()->setPosition(glm::vec3(25, 100, -25));
		torchLight->getLight()->setDirection(glm::vec3(-1.0f, -1.0f, 1.0f));
		torchLight->getLight()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		torchLight->getLight()->setSpotCutOff(glm::pi<GLfloat>() / 4);
		torchLight->getLight()->setMaxDistance(250);

		moon_light = moonLight->getLight();
		torch_light = torchLight->getLight();
		rain_particles = rainEffect->getParticlesManager();
		smoke_particles = smokeEffect->getParticlesManager();
		screen_display = screenDisplay->getScreen();
		tree_model = tree->getModel();

		for (GLuint i = 0; i < Graphics::DirLight::CASCADED_LEVEL; i++) depthMaps[i]->config(2048, 2048);

		rainEffect->getSound()->play();
		smokeEffect->getSound()->play();
}

Demo::~Demo(void)
{
}
