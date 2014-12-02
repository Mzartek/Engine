#include "config.hpp"

inline
static GLfloat getRandomPosition(void)
{
     return (GLfloat)-500 + rand() % 1001;
}

inline
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

     sol->initMeshArray();
     sol->addMesh(sizeof vertexArray / sizeof(Engine::Vertex), vertexArray,
		  sizeof index / sizeof(GLuint), index,
		  "resources/pre-project/feuilles.png", "resources/NM_none.png",
		  mat_ambient, mat_diffuse, mat_specular, mat_shininess);
     sol->genMatNormal();
}

inline
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

	  cepe_tmp->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());
	  phalloide_tmp->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());
	  satan_tmp->matTranslate(getRandomPosition(), 1.5f, getRandomPosition());

	  this->vector_cepe->push_back(cepe_tmp);
	  this->vector_phalloide->push_back(phalloide_tmp);
	  this->vector_satan->push_back(satan_tmp);
     }
}

inline
void GameManager::configTree(void)
{
	model_tree = new Engine::Model(objectProgram, shadowMapProgram);
	model_tree->initMeshArray();
	model_tree->loadFromFile("./resources/tree/Tree1.3ds");
	model_tree->matRotate(-glm::pi<GLfloat>() / 2, 1, 0, 0);
	model_tree->matScale(5, 5, 5);
}

inline
void GameManager::configRainParticles(void)
{
	int numParticle = 1000;
	std::vector<Engine::Particle> rainParticles(numParticle);
    for(int i = 0; i < numParticle; i++)
	{
		rainParticles[i].pos = glm::vec3(rand() % 40 - 20, 50, rand() % 40 - 20);
		rainParticles[i].dir = glm::vec3(0, -1, 0);
		rainParticles[i].life = (GLfloat)(rand() % 100);
    }
    rainManager->setTexture("resources/pre-project/goutte.png");
	rainManager->setParticles(rainParticles.data(), rainParticles.size());
}

GameManager::GameManager(Engine::Renderer *r, Engine::Input *i)
{
     renderer = r;
     input = i;

     skyboxProgram = new Engine::ShaderProgram("shader/skybox/skyboxVert.glsl", NULL, NULL, NULL, "shader/skybox/skyboxFrag.glsl");
     objectProgram = new Engine::ShaderProgram("shader/object/objectVert.glsl", NULL, NULL, "shader/object/objectGeom.glsl", "shader/object/objectFrag.glsl");
     mushroomProgram = new Engine::ShaderProgram("shader/mushroom/mushroomVert.glsl", NULL, NULL, "shader/mushroom/mushroomGeom.glsl", "shader/mushroom/mushroomFrag.glsl");
     dirLightProgram = new Engine::ShaderProgram("shader/dirLight/dirLightVert.glsl", NULL, NULL, NULL, "shader/dirLight/dirLightFrag.glsl");
     spotLightProgram = new Engine::ShaderProgram("shader/spotLight/spotLightVert.glsl", NULL, NULL, NULL, "shader/spotLight/spotLightFrag.glsl");
     shadowMapProgram = new Engine::ShaderProgram("shader/shadow/shadowVert.glsl", NULL, NULL, NULL, "shader/shadow/shadowFrag.glsl");
	 displayRainProgram = new Engine::ShaderProgram("shader/rainParticles/rainVert.glsl", NULL, NULL, "shader/rainParticles/rainGeom.glsl", "shader/rainParticles/rainFrag.glsl");
     backgroundProgram = new Engine::ShaderProgram("shader/background/backgroundVert.glsl", NULL, NULL, NULL, "shader/background/backgroundFrag.glsl");
     screenProgram = new Engine::ShaderProgram("shader/screen/screenVert.glsl", NULL, NULL, NULL, "shader/screen/screenFrag.glsl");
	 textProgram = new Engine::ShaderProgram("shader/text/textVert.glsl", NULL, NULL, NULL, "shader/text/textFrag.glsl");

	 const GLchar *varyings[] = { "outPosition", "outDirection", "outLife" };
	 physicsRainProgram = new Engine::ShaderProgram("shader/rainParticles/rainPhysics.glsl", NULL, NULL, NULL, NULL, varyings, 3);

     gBuffer = new Engine::GBuffer;
     player = new Player;
     skybox = new Engine::SkyBox(skyboxProgram);
     sol = new Engine::Model(objectProgram, shadowMapProgram);
     vector_cepe = new std::vector<Cepe *>;
     vector_phalloide = new std::vector<Phalloide *>;
	 vector_satan = new std::vector<Satan *>;
	 moon = new Engine::DirLight(dirLightProgram);
     torch = new Engine::SpotLight(spotLightProgram);
	 rainManager = new Engine::ParticlesManager(physicsRainProgram, displayRainProgram);
     screen = new Engine::Screen(backgroundProgram, screenProgram);
     text = new Engine::TextArray(textProgram);

     // GBuffer config
     gBuffer->config(renderer->getWidth(), renderer->getHeight());

     // Camera config
     player->getCamera()->setPositionCamera(glm::vec3(30, 5, 0));
     player->getCamera()->setInitialAngle(-glm::pi<GLfloat>() / 2, 0);

     // Skybox config
     skybox->load("resources/Skybox/nnksky01_right.jpg", "resources/Skybox/nnksky01_left.jpg",
		  "resources/Skybox/nnksky01_top.jpg", "resources/Skybox/nnksky01_bottom.jpg",
		  "resources/Skybox/nnksky01_front.jpg", "resources/Skybox/nnksky01_back.jpg");
     skybox->rotate(glm::pi<GLfloat>(), 1, 0, 0);

     // Model config
     configSol();
     configChamp();
	 configTree();

	 moon->setColor(glm::vec3(0.1f, 0.2f, 0.3f));
	 moon->setDirection(glm::vec3(1.0f, -1.0f, 0.0f));
	 moon->setShadowMapping(GL_TRUE);
	 moon->configShadowMap(1024, 1024);

     torch->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
     torch->setSpotCutOff(glm::pi<GLfloat>() / 4);
     torch->setShadowMapping(GL_TRUE);
	 torch->configShadowMap(1024, 1024);

     // ParticlesManager config
     configRainParticles();

     // Text config
     text->setFont("resources/font/SIXTY.TTF", 100, 255, 255, 0);
     text->writeScreen(0 + (renderer->getWidth() - (renderer->getWidth() / 10)), 0,
		       renderer->getWidth() / 10, renderer->getHeight() / 10,
		       renderer, std::to_string(player->getLife()).c_str());
}

GameManager::~GameManager(void)
{
     GLuint i;

     delete text;
     delete screen;
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

	 delete physicsRainProgram;

     delete textProgram;
     delete screenProgram;
     delete backgroundProgram;
	 delete displayRainProgram;
     delete shadowMapProgram;
     delete spotLightProgram;
     delete dirLightProgram;
     delete objectProgram;
     delete mushroomProgram;
     delete skyboxProgram;
}
