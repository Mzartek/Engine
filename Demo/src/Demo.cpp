#include "Demo.hpp"

void Demo::configSol(void)
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
		"../share/Demo/resources/textures/feuilles.png", "../share/Demo/resources/textures/NM_none.png",
		mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	octreeSystem->addModel(sol, 1000);
}

void Demo::configTree(void)
{
	model_tree = new Engine::Model(objectProgram, depthMapProgram);
	model_tree->loadFromFile(
		"../share/Demo/resources/models/tree/Tree1.3ds",
		"../share/Demo/resources/textures/none.png",
		"../share/Demo/resources/textures/NM_none.png");
	model_tree->sortMesh();
	model_tree->setPosition(glm::vec3(50, 0, 50));
	model_tree->setRotation(glm::vec3(-glm::pi<GLfloat>() / 2, 0, 0));
	model_tree->setScale(glm::vec3(5, 5, 5));

	octreeSystem->addModel(model_tree, 40);
}

void Demo::configSmokeParticles(void)
{
	int numParticle = 50;
	std::vector<Engine::Particle> smokeParticles(numParticle);
	for (int i = 0; i < numParticle; i++)
	{
		smokeParticles[i].position = glm::vec3(0, 0, 0);
		smokeParticles[i].direction = glm::vec3((GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX, 1.0f, (GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX);
		smokeParticles[i].velocity = 0.2f;
		smokeParticles[i].life = (GLfloat)(rand() % 100);
	}
	smokeManager->loadTexture("../share/Demo/resources/textures/smoke.png");
	smokeManager->setParticles(smokeParticles.data(), (GLsizei)smokeParticles.size());
	smokeManager->setPosition(glm::vec3(0, 0, 0));
}

Demo::Demo(Engine::Renderer *r, Engine::Input *i, Engine::Audio *a)
{
	renderer = r;
	input = i;
	audio = a;

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

	depthMapProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl");

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

	physicsSmokeProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/smokeParticles/smokePhysics.glsl",
		NULL,
		NULL,
		NULL,
		NULL,
		varyings, sizeof(varyings) / sizeof(GLfloat *));

	gBuffer = new Engine::GBuffer;
	dMaps = new Engine::DepthMap[3];
	camera = new Engine::FreeCam;
	skybox = new Engine::SkyBox(skyboxProgram);
	sol = new Engine::Model(objectProgram, depthMapProgram);
	moon = new Engine::DirLight(dirLightProgram);
	torch = new Engine::SpotLight(spotLightProgram);
	smokeManager = new Engine::ParticlesManager(physicsSmokeProgram, displaySmokeProgram);
	screen = new Engine::Screen(backgroundProgram, screenProgram);
	text = new Engine::TextArray(textProgram);

	octreeSystem = new Engine::OctreeSystem(4, glm::vec3(0, 0, 0), 1000);

	rain_sound = new Engine::Sound;
	fire_sound = new Engine::Sound;

	rainEffect = new RainEffect;

	// GBuffer config
	gBuffer->config(renderer->getWidth(), renderer->getHeight());
	dMaps[0].config(2048, 2048);
	dMaps[1].config(2048, 2048);
	dMaps[2].config(2048, 2048);

	// Camera config
	camera->setCameraPosition(glm::vec3(30, 5, 0));
	camera->setInitialAngle(-glm::pi<GLfloat>() / 2, 0);

	rainEffect->init(camera->getCameraPosition(), 10000);

	// Skybox config
	skybox->load(
		"../share/Demo/resources/textures/skybox/nnksky01_right.jpg", "../share/Demo/resources/textures/skybox/nnksky01_left.jpg",
		"../share/Demo/resources/textures/skybox/nnksky01_top.jpg", "../share/Demo/resources/textures/skybox/nnksky01_bottom.jpg",
		"../share/Demo/resources/textures/skybox/nnksky01_front.jpg", "../share/Demo/resources/textures/skybox/nnksky01_back.jpg");

	// Model config
	configSol();
	configTree();

	moon->setColor(glm::vec3(0.5f, 0.5f, 0.9f));
	moon->setDirection(glm::vec3(0.5f, -1.0f, 0.0f));

	torch->setPosition(glm::vec3(25, 100, -25));
	torch->setDirection(glm::vec3(-1.0f, -1.0f, 1.0f));
	torch->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torch->setSpotCutOff(glm::pi<GLfloat>() / 4);
	torch->setMaxDistance(250);

	// ParticlesManager config
	configSmokeParticles();

	// Text config
	text->setFont("../share/Demo/resources/font/SIXTY.TTF", 100, 255, 255, 0);
	text->writeScreen(0 + (renderer->getWidth() - (renderer->getWidth() / 10)), 0,
		renderer->getWidth() / 10, renderer->getHeight() / 10,
		renderer, "test");

	rain_sound->setGain(0.25f);
	rain_sound->setPitch(1.0f);
	rain_sound->setLoop(AL_TRUE);
	rain_sound->loadFromFile("../share/Demo/resources/sound/rain_stereo.wav", 22050, AL_FORMAT_STEREO16);

	fire_sound->setGain(1.0f);
	fire_sound->setPitch(0.75f);
	fire_sound->setLoop(AL_TRUE);
	fire_sound->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	fire_sound->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	fire_sound->setDistances(1.0f, 100.0f);
	fire_sound->loadFromFile("../share/Demo/resources/sound/fire_mono.wav", 44100, AL_FORMAT_MONO16);

	rain_sound->play();
	fire_sound->play();
}

Demo::~Demo(void)
{
	delete rainEffect;

	delete fire_sound;
	delete rain_sound;

	delete octreeSystem;

	delete text;
	delete screen;
	delete smokeManager;
	delete torch;
	delete moon;
	delete model_tree;
	delete sol;
	delete skybox;
	delete camera;
	delete[] dMaps;
	delete gBuffer;

	delete physicsSmokeProgram;

	delete textProgram;
	delete screenProgram;
	delete backgroundProgram;
	delete displaySmokeProgram;
	delete depthMapProgram;
	delete spotLightProgram;
	delete dirLightProgram;
	delete objectProgram;
	delete skyboxProgram;
}

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	static std::set<Engine::Model *> object;

	// We retrieve object to display from the octree
	object.clear();
	octreeSystem->getModels(gBuffer, camera, &object);

	// Clear Buffers
	renderer->clear();
	gBuffer->clear();

	// Skybox
	skybox->display(gBuffer, camera);

	// Opaque Object
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->display(gBuffer, camera);

	// Lights
	dMaps[0].clear();
	model_tree->displayDepthMap(dMaps, moon);
	moon->display(gBuffer, dMaps, camera);

	dMaps[0].clear();
	dMaps[1].clear();
	dMaps[2].clear();
	model_tree->displayDepthMap(dMaps, torch);
	torch->display(gBuffer, dMaps, camera);

	screen->background(gBuffer);

	// Transparent Object
	for (std::set<Engine::Model *>::iterator it = object.begin(); it != object.end(); it++)
		(*it)->displayTransparent(gBuffer, camera);

	moon->display(gBuffer, camera);
	torch->display(gBuffer, camera);

	screen->background(gBuffer);

	// Particles
	smokeManager->display(gBuffer, camera);
	rainEffect->display(gBuffer, camera);

	screen->display(renderer, gBuffer, 1.0f, 1.0f, 1.0f, 1.0f);

	text->display(renderer);
}

void Demo::idle(long long time)
{
	UNREFERENCED_PARAMETER(time);

	glm::vec3 camPosition;
	glm::vec3 camView;

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
	camView = camera->getViewVector();

	moon->position(camPosition, 100, 250, 500);
	torch->position(dMaps);

	smokeManager->updateParticles();
	rainEffect->updateParticles(camPosition);

	audio->setListenerPosition(camPosition, camView);
}

void Demo::reshape(GLuint w, GLuint h)
{
	camera->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}

void Demo::launch(void)
{
	renderer->mainLoop(this);
}