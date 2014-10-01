#include "config.hpp"

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
	cam = new Engine::FreeCam;
	skybox = new Engine::SkyBox(skyboxProgram);
	sol = new Engine::Model(objectProgram, shadowMapProgram);
	heli = new Engine::Model(objectProgram, shadowMapProgram);
	sun = new Engine::DirLight(dirLightProgram);
	torch = new Engine::SpotLight(spotLightProgram);
	screen = new Engine::Screen(backgroundProgram, screenProgram);
	text = new Engine::TextArray(textProgram);

	// GBuffer config
	gBuffer->config(renderer->getWidth(), renderer->getHeight());

	// Camera config
	cam->setPositionCamera(glm::vec3(30, 10, 0));
	cam->setInitialAngle(-90, 0);

	// Skybox config
	skybox->load("resources/Skybox/rightred2.jpg", "resources/Skybox/leftred2.jpg",
		"resources/Skybox/topred2.jpg", "resources/Skybox/botred2.jpg",
		"resources/Skybox/frontred2.jpg", "resources/Skybox/backred2.jpg");
	skybox->rotate(180, 1, 0, 0);

	// Model config
	GLfloat vertexArray[] =
	{
		-500, 0, -500, 0, 0, 0, 1, 0, 1, 0, 0,
		-500, 0, 500, 0, 1, 0, 1, 0, 1, 0, 0,
		500, 0, 500, 1, 1, 0, 1, 0, 1, 0, 0,
		500, 0, -500, 1, 0, 0, 1, 0, 1, 0, 0
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };
	glm::vec4 mat_ambient(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 mat_diffuse(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 mat_specular(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat mat_shininess = 20.0f;

	sol->initMeshArray();
	sol->addMesh(sizeof vertexArray, vertexArray,
		sizeof index, index,
		"resources/ornaments.jpg", "resources/NM_none.png",
		mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	heli->initMeshArray();
	heli->loadFromFile("resources/UH-60_Blackhawk/corps.mobj");
	heli->sortMesh();
	heli->matTranslate(0.0f, 6.0f, 0.0f);
	heli->matScale(2, 2, 2);

	// Light config
	sun->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	sun->setDirection(glm::vec3(1.0f, -1.0f, 0.0f));
	sun->setShadowMapping(GL_TRUE);
	sun->configShadowMap(1024, 1024);

	torch->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	torch->setPosition(glm::vec3(20.0f, 40.0f, 0.0f));
	torch->setDirection(glm::vec3(-0.5f, -1.0f, 0.0f));
	torch->setSpotCutOff(45.0f);
	torch->setShadowMapping(GL_TRUE);
	torch->configShadowMap(1024, 1024);

	// Text config
	text->setFont("resources/font/SIXTY.TTF", 100, 255, 255, 0);
	text->writeScreen((renderer->getWidth() / 2) - 200, (renderer->getHeight() / 2) + 100, 400, 100, renderer, "Coucou!");
}

GameManager::~GameManager(void)
{
	delete text;
	delete screen;
	delete torch;
	delete sun;
	delete heli;
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
