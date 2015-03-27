#include "config.hpp"

static GLfloat getRandomPosition(void)
{
	return (GLfloat)-500 + rand() % 1000;
}

void GameManager::configSol(void)
{
	Engine::Vertex vertexArray[] =
	{
		glm::vec3(-500, 0, -500), glm::vec2(0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(-500, 0, 500), glm::vec2(0, 50), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(500, 0, 500), glm::vec2(50, 50), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(500, 0, -500), glm::vec2(50, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };
	glm::vec4 mat_ambient(0.1f, 0.1f, 0.1f, 1.0f);
	glm::vec4 mat_diffuse(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 mat_specular(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat mat_shininess = 8.0f;

	sol->addMesh(sizeof vertexArray / sizeof(Engine::Vertex), vertexArray,
		sizeof index / sizeof(GLuint), index,
		"../share/Demo/resources/pre-project/feuilles.png", "../share/Demo/resources/NM_none.png",
		mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	octreeSystem->addModel(sol, 1000);
}

void GameManager::configChamp(void)
{
	Cepe *cepe_tmp;
	Phalloide *phalloide_tmp;
	Satan *satan_tmp;

	model_cepe = new Cepe(mushroomProgram, shadowMapProgram);
	model_phalloide = new Phalloide(mushroomProgram, shadowMapProgram);
	model_satan = new Satan(mushroomProgram, shadowMapProgram);

	for (GLuint i = 1; i < 20; i++)
	{
		cepe_tmp = new Cepe(model_cepe);
		phalloide_tmp = new Phalloide(model_phalloide);
		satan_tmp = new Satan(model_satan);

		cepe_tmp->setPosition(glm::vec3(getRandomPosition(), 1.5f, getRandomPosition()));
		phalloide_tmp->setPosition(glm::vec3(getRandomPosition(), 1.5f, getRandomPosition()));
		satan_tmp->setPosition(glm::vec3(getRandomPosition(), 1.5f, getRandomPosition()));

		octreeSystem->addModel(cepe_tmp, 2);
		octreeSystem->addModel(phalloide_tmp, 2);
		octreeSystem->addModel(satan_tmp, 2);

		vector_cepe->push_back(cepe_tmp);
		vector_phalloide->push_back(phalloide_tmp);
		vector_satan->push_back(satan_tmp);
	}
}

void GameManager::configTree(void)
{
	model_tree = new Engine::Model(objectProgram, shadowMapProgram);
	model_tree->loadFromFile(
	     "../share/Demo/resources/tree/Tree1.3ds",
	     "../share/Demo/resources/none.png",
	     "../share/Demo/resources/NM_none.png");
	model_tree->sortMesh();
	model_tree->setPosition(glm::vec3(50, 0, 50));
	model_tree->setRotation(glm::vec3(-glm::pi<GLfloat>() / 2, 0, 0));
	model_tree->setScale(glm::vec3(5, 5, 5));

	octreeSystem->addModel(model_tree, 40);
}

void GameManager::configRainParticles(void)
{
	int numParticle = 10000;
	std::vector<Engine::Particle> rainParticles(numParticle);
	glm::vec3 pos = player->getCamera()->getCameraPosition();
	for (int i = 0; i < numParticle; i++)
	{
	        rainParticles[i].position = glm::vec3(pos.x + (rand() % 200 - 100), pos.y + 100, pos.z + (rand() % 200 - 100));
		rainParticles[i].direction = glm::vec3(0, -1, 0);
		rainParticles[i].velocity = 2.0f;
		rainParticles[i].life = (GLfloat)(rand() % 100);
	}
	rainManager->setTexture("../share/Demo/resources/pre-project/goutte.png");
	rainManager->setParticles(rainParticles.data(), (GLsizei)rainParticles.size());
}

void GameManager::configSmokeParticles(void)
{
	int numParticle = 50;
	std::vector<Engine::Particle> smokeParticles(numParticle);
	for (int i = 0; i < numParticle; i++)
	{
		smokeParticles[i].position = glm::vec3(0, 0, 0);
		smokeParticles[i].direction = glm::vec3((GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX, 0.75f, 0);
		smokeParticles[i].velocity = 0.2f;
		smokeParticles[i].life = (GLfloat)(rand() % 100);
	}
	smokeManager->setTexture("../share/Demo/resources/pre-project/smoke.png");
	smokeManager->setParticles(smokeParticles.data(), (GLsizei)smokeParticles.size());
	smokeManager->setPosition(glm::vec3(0, 0, 0));
}

GameManager::GameManager(Engine::Renderer *r, Engine::Input *i)
{
	renderer = r;
	input = i;

	skyboxProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/skybox/skyboxVert.glsl",
	     NULL,
	     NULL,
	     NULL,
	     "../share/Demo/shader/skybox/skyboxFrag.glsl");
	
	objectProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/object/objectVert.glsl",
	     NULL,
	     NULL,
	     "../share/Demo/shader/object/objectGeom.glsl",
	     "../share/Demo/shader/object/objectFrag.glsl");
	
	mushroomProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/mushroom/mushroomVert.glsl",
	     NULL,
	     NULL,
	     "../share/Demo/shader/mushroom/mushroomGeom.glsl",
	     "../share/Demo/shader/mushroom/mushroomFrag.glsl");
	
	dirLightProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/dirLight/dirLightVert.glsl",
	     NULL,
	     NULL,
	     NULL,
	     "../share/Demo/shader/dirLight/dirLightFrag.glsl");
	
	spotLightProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/spotLight/spotLightVert.glsl",
	     NULL,
	     NULL,
	     NULL,
	     "../share/Demo/shader/spotLight/spotLightFrag.glsl");
	
	shadowMapProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/shadow/shadowVert.glsl",
	     NULL,
	     NULL,
	     NULL,
	     "../share/Demo/shader/shadow/shadowFrag.glsl");
	
	displayRainProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/rainParticles/rainVert.glsl",
	     NULL,
	     NULL,
	     "../share/Demo/shader/rainParticles/rainGeom.glsl",
	     "../share/Demo/shader/rainParticles/rainFrag.glsl");
	
	displaySmokeProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/smokeParticles/smokeVert.glsl",
	     NULL,
	     NULL,
	     "../share/Demo/shader/smokeParticles/smokeGeom.glsl",
	     "../share/Demo/shader/smokeParticles/smokeFrag.glsl");
	
	backgroundProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/background/backgroundVert.glsl",
	     NULL,
	     NULL,
	     NULL,
	     "../share/Demo/shader/background/backgroundFrag.glsl");
	
	screenProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/screen/screenVert.glsl",
	     NULL,
	     NULL,
	     NULL,
	     "../share/Demo/shader/screen/screenFrag.glsl");
	
	textProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/text/textVert.glsl",
	     NULL,
	     NULL,
	     NULL,
	     "../share/Demo/shader/text/textFrag.glsl");

	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };
	
	physicsRainProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/rainParticles/rainPhysics.glsl",
	     NULL,
	     NULL,
	     NULL,
	     NULL,
	     varyings, sizeof(varyings) / sizeof(GLfloat *));
	
	physicsSmokeProgram = new Engine::ShaderProgram(
	     "../share/Demo/shader/smokeParticles/smokePhysics.glsl",
	     NULL,
	     NULL,
	     NULL,
	     NULL,
	     varyings, sizeof(varyings) / sizeof(GLfloat *));

	gBuffer = new Engine::GBuffer;
	player = new Player;
	skybox = new Engine::SkyBox(skyboxProgram);
	sol = new Engine::Model(objectProgram, shadowMapProgram);
	vector_cepe = new std::vector < Cepe * > ;
	vector_phalloide = new std::vector < Phalloide * > ;
	vector_satan = new std::vector < Satan * > ;
	moon = new Engine::DirLight(dirLightProgram);
	torch = new Engine::SpotLight(spotLightProgram);
	rainManager = new Engine::ParticlesManager(physicsRainProgram, displayRainProgram);
	smokeManager = new Engine::ParticlesManager(physicsSmokeProgram, displaySmokeProgram);
	screen = new Engine::Screen(backgroundProgram, screenProgram);
	text = new Engine::TextArray(textProgram);

	octreeSystem = new Engine::OctreeSystem(4, glm::vec3(0, 0, 0), 1000);

	// GBuffer config
	gBuffer->config(renderer->getWidth(), renderer->getHeight());

	// Camera config
	player->getCamera()->setCameraPosition(glm::vec3(30, 5, 0));
	player->getCamera()->setInitialAngle(-glm::pi<GLfloat>() / 2, 0);

	// Skybox config
	skybox->load(
	     "../share/Demo/resources/Skybox/nnksky01_right.jpg", "../share/Demo/resources/Skybox/nnksky01_left.jpg",
	     "../share/Demo/resources/Skybox/nnksky01_top.jpg",   "../share/Demo/resources/Skybox/nnksky01_bottom.jpg",
	     "../share/Demo/resources/Skybox/nnksky01_front.jpg", "../share/Demo/resources/Skybox/nnksky01_back.jpg");

	// Model config
	configSol();
	configChamp();
	configTree();

	moon->setColor(glm::vec3(0.5f, 0.5f, 0.9f));
	moon->setDirection(glm::vec3(0.5f, -1.0f, 0.0f));
	moon->setShadowMapping(GL_TRUE);
	moon->configShadowMap(2048, 2048);

	torch->setPosition(glm::vec3(25, 100, -25));
	torch->setDirection(glm::vec3(-1.0f, -1.0f, 1.0f));
	torch->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torch->setSpotCutOff(glm::pi<GLfloat>() / 4);
	torch->setMaxDistance(250);
	torch->setShadowMapping(GL_TRUE);
	torch->configShadowMap(2048, 2048);

	// ParticlesManager config
	configRainParticles();
	configSmokeParticles();

	// Text config
	text->setFont("../share/Demo/resources/font/SIXTY.TTF", 100, 255, 255, 0);
	text->writeScreen(0 + (renderer->getWidth() - (renderer->getWidth() / 10)), 0,
		renderer->getWidth() / 10, renderer->getHeight() / 10,
		renderer, std::to_string(player->getLife()).c_str());
}

GameManager::~GameManager(void)
{
	GLuint i;

	delete octreeSystem;

	delete text;
	delete screen;
	delete smokeManager;
	delete rainManager;
	delete torch;
	delete moon;
	for (i = 0; i < vector_satan->size(); i++)
		delete (*vector_satan)[i];
	for (i = 0; i < vector_phalloide->size(); i++)
		delete (*vector_phalloide)[i];
	for (i = 0; i < vector_cepe->size(); i++)
		delete (*vector_cepe)[i];
	delete vector_satan;
	delete vector_phalloide;
	delete vector_cepe;
	delete model_tree;
	delete model_satan;
	delete model_phalloide;
	delete model_cepe;
	delete sol;
	delete skybox;
	delete player;
	delete gBuffer;

	delete physicsSmokeProgram;
	delete physicsRainProgram;

	delete textProgram;
	delete screenProgram;
	delete backgroundProgram;
	delete displaySmokeProgram;
	delete displayRainProgram;
	delete shadowMapProgram;
	delete spotLightProgram;
	delete dirLightProgram;
	delete objectProgram;
	delete mushroomProgram;
	delete skyboxProgram;
}
