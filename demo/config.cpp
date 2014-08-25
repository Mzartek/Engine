#include "config.hpp"

void configShaders(void)
{
	objectProgram->loadProgram("shader/object/gObjectVert.glsl", NULL, NULL, "shader/object/gObjectGeom.glsl", "shader/object/gObjectFrag.glsl");
	dirLightProgram->loadProgram("shader/dirLight/gDirLightVert.glsl", NULL, NULL, NULL, "shader/dirLight/gDirLightFrag.glsl");
	spotLightProgram->loadProgram("shader/spotLight/gSpotLightVert.glsl", NULL, NULL, NULL, "shader/spotLight/gSpotLightFrag.glsl");
	shadowProgram->loadProgram("shader/shadow/shadowVert.glsl", NULL, NULL, NULL, "shader/shadow/shadowFrag.glsl");
	skyboxProgram->loadProgram("shader/skybox/gSkyboxVert.glsl", NULL, NULL, NULL, "shader/skybox/gSkyboxFrag.glsl");
	screenProgram->loadProgram("shader/screen/screenVert.glsl", NULL, NULL, NULL, "shader/screen/screenFrag.glsl");
	textProgram->loadProgram("shader/text/textVert.glsl", NULL, NULL, NULL, "shader/text/textFrag.glsl");
}

void configBuffers(void)
{
	gBuffer->config(renderer->getWidth(), renderer->getHeight());
}

void configText(void)
{
	text1->config("resources/font/SIXTY.TTF", 100,
		      255, 255, 255,
			  (renderer->getWidth() / 2) - 200, (renderer->getHeight() / 2) + 100,
			  400, 100, textProgram, renderer);
	text1->write("Coucou!");
	text2->config("resources/font/SIXTY.TTF", 100,
		      255, 255, 255,
			  (renderer->getWidth() / 2) - 200, (renderer->getHeight() / 2),
			  400, 100, textProgram, renderer);
	text3->config("resources/font/SIXTY.TTF", 50,
		      255, 255, 255,
			  (renderer->getWidth() / 2) - 200, (renderer->getHeight() / 2) - 100,
			  400, 100, textProgram, renderer);
}

void configLights(void)
{
	sun->config(dirLightProgram);
	sun->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	sun->setDirection(glm::vec3(1.0f, -1.0f, 0.0f));
	sun->activateShadowMapping(GL_TRUE);
	sun->configShadowMap(1024, 1024, shadowProgram);

    torch->config(spotLightProgram);
    torch->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    torch->setPosition(glm::vec3(20.0f, 40.0f, 0.0f));
    torch->setDirection(glm::vec3(-0.5f, -1.0f, 0.0f));
    torch->setSpotCutOff(45.0f);
	torch->activateShadowMapping(GL_TRUE);
	torch->configShadowMap(1024, 1024, shadowProgram);
}

void configScreen(void)
{
	screen->config(screenProgram);
}

void configModels(void)
{
	GLfloat vertex[] = {
		-500, 0, -500,
		0, 0,//
		0, 1, 0,
		-500, 0, 500,
		0, 1,//
		0, 1, 0,
		500, 0, 500,
		1, 1,//
		0, 1, 0,
		500, 0, -500,
		1, 0,//
		0, 1, 0
	};
	GLuint index[] = { 0, 1, 2, 0, 2, 3 };
	glm::vec4 mat_ambient(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 mat_diffuse(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 mat_specular(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat mat_shininess = 20.0f;

	sol->config(objectProgram);
	sol->initGLObjectArray();
	sol->createGLObject(sizeof vertex, vertex,
			   sizeof index, index,
			   "resources/ornaments.jpg",
			   mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	//Helicopter
	heli->config(objectProgram);
	heli->initGLObjectArray();
	heli->loadFromFile("resources/UH-60_Blackhawk/corps.obj");
	heli->sortGLObject();
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
