#include "config.hpp"

void configShaders(void)
{
	objectProgram->loadProgram("shader/object/objectVert.glsl", NULL, NULL, "shader/object/objectGeom.glsl", "shader/object/objectFrag.glsl");
	dirLightProgram->loadProgram("shader/dirLight/dirLightVert.glsl", NULL, NULL, NULL, "shader/dirLight/dirLightFrag.glsl");
	spotLightProgram->loadProgram("shader/spotLight/spotLightVert.glsl", NULL, NULL, NULL, "shader/spotLight/spotLightFrag.glsl");
	shadowMapProgram->loadProgram("shader/shadow/shadowVert.glsl", NULL, NULL, NULL, "shader/shadow/shadowFrag.glsl");
	skyboxProgram->loadProgram("shader/skybox/skyboxVert.glsl", NULL, NULL, NULL, "shader/skybox/skyboxFrag.glsl");
	backgroundProgram->loadProgram("shader/background/backgroundVert.glsl", NULL, NULL, NULL, "shader/background/backgroundFrag.glsl");
	screenProgram->loadProgram("shader/screen/screenVert.glsl", NULL, NULL, NULL, "shader/screen/screenFrag.glsl");
	textProgram->loadProgram("shader/text/textVert.glsl", NULL, NULL, NULL, "shader/text/textFrag.glsl");
}

void configBuffers(void)
{
	gBuffer->config(renderer->getWidth(), renderer->getHeight());
}

void configText(void)
{
	text->config("resources/font/SIXTY.TTF", 100,
		      255, 255, 255,
			  (renderer->getWidth() / 2) - 200, (renderer->getHeight() / 2) + 100,
			  400, 100, textProgram, renderer);
	text->write("Coucou!");
}

void configLights(void)
{
	sun->config(dirLightProgram);
	sun->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	sun->setDirection(glm::vec3(1.0f, -1.0f, 0.0f));
	sun->setShadowMapping(GL_TRUE);
	sun->configShadowMap(1024, 1024);

    torch->config(spotLightProgram);
    torch->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    torch->setPosition(glm::vec3(20.0f, 40.0f, 0.0f));
    torch->setDirection(glm::vec3(-0.5f, -1.0f, 0.0f));
    torch->setSpotCutOff(45.0f);
	torch->setShadowMapping(GL_TRUE);
	torch->configShadowMap(1024, 1024);
}

void configScreen(void)
{
	screen->config(backgroundProgram, screenProgram);
}

void configModels(void)
{
	engine::Vertex vertexArray[] = {
			{ glm::vec3(-500, 0, -500), glm::vec2(0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0) },
			{ glm::vec3(-500, 0, 500), glm::vec2(0, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0) },
			{ glm::vec3(500, 0, 500), glm::vec2(1, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0) },
			{ glm::vec3(500, 0, -500), glm::vec2(1, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0) }
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };
	glm::vec4 mat_ambient(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 mat_diffuse(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 mat_specular(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat mat_shininess = 20.0f;

	sol->config(objectProgram, shadowMapProgram);
	sol->initMeshArray();
	sol->createMesh(sizeof vertexArray, (GLfloat *)vertexArray,
			   sizeof index, index,
			   "resources/ornaments.jpg", "resources/NM_none.png",
			   mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	//Helicopter
	heli->config(objectProgram, shadowMapProgram);
	heli->initMeshArray();
	heli->loadFromFile("resources/UH-60_Blackhawk/corps.mobj");
	heli->sortMesh();
	heli->matTranslate(0.0f, 6.0f, 0.0f);
	heli->matScale(2, 2, 2);
}

void configSkybox(void)
{
	skybox->load("resources/Skybox/rightred2.jpg", "resources/Skybox/leftred2.jpg",
		     "resources/Skybox/topred2.jpg", "resources/Skybox/botred2.jpg",
		     "resources/Skybox/frontred2.jpg", "resources/Skybox/backred2.jpg",
			 10, skyboxProgram);
	skybox->rotate(180, 1, 0, 0);
}
