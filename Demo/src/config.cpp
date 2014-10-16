#include "config.hpp"

inline
static GLfloat getRandomPosition(void)
{
	return (GLfloat)-500 + rand() % 1001;
}

inline
void GameManager::configSol(void)
{
	GLfloat vertexArray[] =
	{
		-500, 0, -500, 0, 0, 0, 1, 0, 1, 0, 0,
		-500, 0, 500, 0, 50, 0, 1, 0, 1, 0, 0,
		500, 0, 500, 50, 50, 0, 1, 0, 1, 0, 0,
		500, 0, -500, 50, 0, 0, 1, 0, 1, 0, 0
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };
	glm::vec4 mat_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec4 mat_diffuse(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 mat_specular(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat mat_shininess = 20.0f;

	sol->initMeshArray();
	sol->addMesh(sizeof vertexArray, vertexArray,
		sizeof index, index,
		"resources/pre-project/feuilles.png", "resources/NM_none.png",
		mat_ambient, mat_diffuse, mat_specular, mat_shininess);
}

inline
void GameManager::configChamp(void)
{
	GLuint i;
	GLfloat vertexArray[] =
	{
		-1.0f, -1.5f, 0, 0, 0, 0, 0, 1, 0, 1, 0,
		-1.0f, 1.5f, 0, 0, 1, 0, 0, 1, 0, 1, 0,
		1.0f, 1.5f, 0, 1, 1, 0, 0, 1, 0, 1, 0,
		1.0f, -1.5f, 0, 1, 0, 0, 0, 1, 0, 1, 0
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };
	glm::vec4 mat_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec4 mat_diffuse(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 mat_specular(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat mat_shininess = 20.0f;

	Engine::Model *cepe1, *cepe0 = new Engine::Model(objectProgram, shadowMapProgram);
	Engine::Model *phalloide1, *phalloide0 = new Engine::Model(objectProgram, shadowMapProgram);
	Engine::Model *satan1, *satan0 = new Engine::Model(objectProgram, shadowMapProgram);

	cepe0->initMeshArray();
	phalloide0->initMeshArray();
	satan0->initMeshArray();

	cepe0->addMesh(sizeof vertexArray, vertexArray,
		sizeof index, index,
		"resources/pre-project/cepe.png", "resources/NM_none.png",
		mat_ambient, mat_diffuse, mat_specular, mat_shininess);
	phalloide0->addMesh(sizeof vertexArray, vertexArray,
		sizeof index, index,
		"resources/pre-project/phalloide.png", "resources/NM_none.png",
		mat_ambient, mat_diffuse, mat_specular, mat_shininess);
	satan0->addMesh(sizeof vertexArray, vertexArray,
		sizeof index, index,
		"resources/pre-project/satan.png", "resources/NM_none.png",
		mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	cepe0->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());
	phalloide0->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());
	satan0->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());

	this->cepe->push_back(cepe0);
	this->phalloide->push_back(phalloide0);
	this->satan->push_back(satan0);

	for (i = 1; i < 20; i++)
	{
		cepe1 = new Engine::Model(objectProgram, shadowMapProgram);
		phalloide1 = new Engine::Model(objectProgram, shadowMapProgram);
		satan1 = new Engine::Model(objectProgram, shadowMapProgram);

		cepe1->initMeshMirror(cepe0);
		phalloide1->initMeshMirror(phalloide0);
		satan1->initMeshMirror(satan0);

		cepe1->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());
		phalloide1->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());
		satan1->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());

		this->cepe->push_back(cepe1);
		this->phalloide->push_back(phalloide1);
		this->satan->push_back(satan1);
	}
}

GameManager::GameManager(Engine::Renderer *r, Engine::Input *i)
{
	renderer = r;
	input = i;

	skyboxProgram = new Engine::ShaderProgram("shader/skybox/skyboxVert.glsl", NULL, NULL, NULL, "shader/skybox/skyboxFrag.glsl");
	objectProgram = new Engine::ShaderProgram("shader/object/objectVert.glsl", NULL, NULL, "shader/object/objectGeom.glsl", "shader/object/objectFrag.glsl");
	dirLightProgram = new Engine::ShaderProgram("shader/dirLight/dirLightVert.glsl", NULL, NULL, NULL, "shader/dirLight/dirLightFrag.glsl");
	spotLightProgram = new Engine::ShaderProgram("shader/spotLight/spotLightVert.glsl", NULL, NULL, NULL, "shader/spotLight/spotLightFrag.glsl");
	shadowMapProgram = new Engine::ShaderProgram("shader/shadow/shadowVert.glsl", NULL, NULL, NULL, "shader/shadow/shadowFrag.glsl");
	backgroundProgram = new Engine::ShaderProgram("shader/background/backgroundVert.glsl", NULL, NULL, NULL, "shader/background/backgroundFrag.glsl");
	screenProgram = new Engine::ShaderProgram("shader/screen/screenVert.glsl", NULL, NULL, NULL, "shader/screen/screenFrag.glsl");
	textProgram = new Engine::ShaderProgram("shader/text/textVert.glsl", NULL, NULL, NULL, "shader/text/textFrag.glsl");

	gBuffer = new Engine::GBuffer;
	cam = new Engine::PlayerCam;
	skybox = new Engine::SkyBox(skyboxProgram);
	sol = new Engine::Model(objectProgram, shadowMapProgram);
	cepe = new std::vector<Engine::Model *>;
	phalloide = new std::vector<Engine::Model *>;
	satan = new std::vector<Engine::Model *>;
	torch = new Engine::SpotLight(spotLightProgram);
	screen = new Engine::Screen(backgroundProgram, screenProgram);
	text = new Engine::TextArray(textProgram);

	// GBuffer config
	gBuffer->config(renderer->getWidth(), renderer->getHeight());

	// Camera config
	cam->setPositionCamera(glm::vec3(30, 5, 0));
	cam->setInitialAngle(-90, 0);

	// Skybox config
	skybox->load("resources/Skybox/rightred2.jpg", "resources/Skybox/leftred2.jpg",
		"resources/Skybox/topred2.jpg", "resources/Skybox/botred2.jpg",
		"resources/Skybox/frontred2.jpg", "resources/Skybox/backred2.jpg");
	skybox->rotate(180, 1, 0, 0);

	// Model config
	configSol();
	configChamp();

	torch->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torch->setSpotCutOff(45.0f);
	torch->setShadowMapping(GL_TRUE);
	torch->configShadowMap(1024, 1024);

	// Text config
	text->setFont("resources/font/SIXTY.TTF", 100, 255, 255, 0);
	text->writeScreen((renderer->getWidth() / 2) - 200, (renderer->getHeight() / 2) + 100, 400, 100, renderer, "Coucou!");
}

GameManager::~GameManager(void)
{
	GLuint i;

	delete text;
	delete screen;
	delete torch;
	for (i = 0; i < satan->size(); i++)
	{
		delete (*satan)[i];
		delete (*phalloide)[i];
		delete (*cepe)[i];
	}
	delete satan;
	delete phalloide;
	delete cepe;
	delete sol;
	delete skybox;
	delete cam;
	delete gBuffer;

	delete textProgram;
	delete screenProgram;
	delete backgroundProgram;
	delete shadowMapProgram;
	delete spotLightProgram;
	delete dirLightProgram;
	delete objectProgram;
	delete skyboxProgram;
}
