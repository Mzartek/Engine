#include "Demo.hpp"

Demo::Demo(void)
{
	backgroundProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/background/backgroundVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/background/backgroundFrag.glsl");

	windowProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/screen/screenVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/screen/windowFrag.glsl");
	
	gbuffer = std::make_shared<Graphics::GBuffer>();
	gbuffer->config(
		Graphics::GraphicsRenderer::Instance().getWidth(),
		Graphics::GraphicsRenderer::Instance().getHeight());

	camera = std::make_shared<Graphics::FreeCam>();

	octree = std::make_shared<Graphics::Octree>(4, glm::vec3(0, 0, 0), 1000.0f);

	nightBox = std::make_shared<NightBox>();
	tree = std::make_shared<Tree>();
	animModel = std::make_shared<AnimModel>();
	ground = std::make_shared<Ground>();
	moonLight = std::make_shared<MoonLight>();
	torchLight = std::make_shared<TorchLight>();
	rainEffect = std::make_shared<RainEffect>();
	smokeEffect = std::make_shared<SmokeEffect>();
	bloomPost = std::make_shared<BloomPost>(
		Graphics::GraphicsRenderer::Instance().getWidth(),
		Graphics::GraphicsRenderer::Instance().getHeight());

	for (GLuint i = 0; i < Graphics::DirLight::CASCADED_LEVEL; i++)
	{
		depthMaps.push_back(std::make_shared<Graphics::DepthMap>());
		depthMaps[i]->config(2048, 2048);
	}

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

	rainEffect->getSound()->play();
	smokeEffect->getSound()->play();
}

Demo::~Demo(void)
{
}
