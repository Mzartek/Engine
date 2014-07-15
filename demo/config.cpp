#include "config.hpp"

void configShaders(void)
{
	objectProgram = new engine::ShaderProgram;
	lightProgram = new engine::ShaderProgram;
	shadowProgram = new engine::ShaderProgram;
	skyboxProgram = new engine::ShaderProgram;
	screenProgram = new engine::ShaderProgram;
	textProgram = new engine::ShaderProgram;

	objectProgram->loadProgram("shader/objectVert.glsl", "shader/objectFrag.glsl");
	lightProgram->loadProgram("shader/dirLightVert.glsl", "shader/dirLightFrag.glsl");
	shadowProgram->loadProgram("shader/shadowVert.glsl", "shader/shadowFrag.glsl");
	skyboxProgram->loadProgram("shader/skyboxVert.glsl", "shader/skyboxFrag.glsl");
	screenProgram->loadProgram("shader/screenVert.glsl", "shader/screenFrag.glsl");
	textProgram->loadProgram("shader/textVert.glsl", "shader/textFrag.glsl");
}

void configBuffers(void)
{
	gBuffer->config(window->getWidth(), window->getHeight());
}

void configText(void)
{
	text1->config("resources/font/SIXTY.TTF", 100,
		      255, 255, 255,
		      (window->getWidth() / 2) - 200, (window->getHeight() / 2) + 100,
		      400, 100, textProgram, window);
	text1->write("Coucou!");
	text2->config("resources/font/SIXTY.TTF", 100,
		      255, 255, 255,
		      (window->getWidth() / 2) - 200, (window->getHeight() / 2),
		      400, 100, textProgram, window);
	text3->config("resources/font/SIXTY.TTF", 50,
		      255, 255, 255,
		      (window->getWidth() / 2) - 200, (window->getHeight() / 2) - 100,
		      400, 100, textProgram, window);
}

void configLights(void)
{
	GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	sun->config(lightProgram);
	sun->setDirection(1, -1, 0);
	sun->setColor(lightColor[0], lightColor[1], lightColor[2]);
	sun->configShadowMap(1024, 1024, shadowProgram);
	sun->setMatrixDimension(50);
}

void configScreen(void)
{
	screen->config(screenProgram);
	sa = 0.0f;
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
	GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 20.0f };

	face->initObjectArray();
	face->config(objectProgram);
	face->createObject(sizeof vertex, vertex,
			   sizeof index, index,
			   "resources/ornaments.jpg",
			   mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	//Cubes
	cube1->config(objectProgram);
	cube1->initObjectArray();
	cube1->loadObj("resources/Crate/crate.obj");
	cube1->sortObject();

	cube2->config(objectProgram);
	cube2->initObjectMirror(cube1);

	cube3->config(objectProgram);
	cube3->initObjectMirror(cube1);

	cube4->config(objectProgram);
	cube4->initObjectMirror(cube1);

	//Helicopter
	helicopter->config(objectProgram);
	helicopter->initObjectArray();
	helicopter->loadFromFile("resources/UH-60_Blackhawk/corps.obj");
	helicopter->sortObject();

	grotor->config(objectProgram);
	grotor->initObjectArray();
	grotor->loadFromFile("resources/UH-60_Blackhawk/grotor.obj");
	grotor->sortObject();

	protor->config(objectProgram);
	protor->initObjectArray();
	protor->loadFromFile("resources/UH-60_Blackhawk/protor.obj");
	protor->sortObject();
}

void configSkybox(void)
{
	skybox->load("resources/Skybox/rightred2.jpg", "resources/Skybox/leftred2.jpg",
		     "resources/Skybox/topred2.jpg", "resources/Skybox/botred2.jpg",
		     "resources/Skybox/frontred2.jpg", "resources/Skybox/backred2.jpg",
		     100, skyboxProgram);
	skybox->rotate(0, 0, 0, 0);
}
