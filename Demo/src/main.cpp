#include "config.hpp"

GLboolean keyState[256];

engine::Renderer *renderer;
engine::FreeCam *cam;
engine::DirLight *sun;
engine::SpotLight *torch;
engine::Model *sol;
engine::Model *heli;
engine::SkyBox *skybox;
engine::Screen *screen;
engine::TextArray *text;
engine::GBuffer *gBuffer;

engine::ShaderProgram *objectProgram;
engine::ShaderProgram *dirLightProgram;
engine::ShaderProgram *spotLightProgram;
engine::ShaderProgram *shadowMapProgram;
engine::ShaderProgram *skyboxProgram;
engine::ShaderProgram *backgroundProgram;
engine::ShaderProgram *screenProgram;
engine::ShaderProgram *textProgram;

void display(void)
{
	renderer->clear();
	gBuffer->clear();
	sun->clear();
	torch->clear();

	// Skybox
	skybox->display(gBuffer, cam);

	// Shadow
	sol->displayShadowMap(sun);
	heli->displayShadowMap(sun);
	sol->displayShadowMap(torch);
	heli->displayShadowMap(torch);

	// Opaque Object
	sol->display(gBuffer, cam);
	heli->display(gBuffer, cam);
	sun->display(gBuffer, cam);
	torch->display(gBuffer, cam);
	screen->background(gBuffer);

	// Transparent Object
	sol->displayTransparent(gBuffer, cam);
	heli->displayTransparent(gBuffer, cam);
	sun->display(gBuffer, cam);
	torch->display(gBuffer, cam);
	screen->background(gBuffer);

	screen->display(renderer, gBuffer, 1.0, 1.0, 1.0, 1.0);

	//text->display(renderer);
}

void idle(void)
{
	cam->keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);

	heli->matRotate(0.1f, 0, 1, 0);

	cam->position();
	sun->position(heli->getPosition(), 25);
	torch->position();
}

void reshape(GLuint w, GLuint h)
{
	cam->setPerspective(90.0f, w, h, 0.1f, 1000.0f);
}

void keyboard(GLubyte key, GLboolean state)
{
	keyState[key] = state;

	if(keyState[MAJ]==GL_TRUE)
		cam->setSpeed(0.05f);
	else
		cam->setSpeed(0.25f);

	if (state)
		switch (key)
		{
		case ESC:
			renderer->stopLoop();
			break;
		}
}

void mouseMove(GLint xrel, GLint yrel)
{
	cam->mouseMove(xrel, yrel);
}

void init(void)
{
	cam = new engine::FreeCam;
	sun = new engine::DirLight;
	torch = new engine::SpotLight;
	sol = new engine::Model;
	heli = new engine::Model;
	skybox = new engine::SkyBox;
	screen = new engine::Screen;
	text = new engine::TextArray;
	gBuffer = new engine::GBuffer;

	objectProgram = new engine::ShaderProgram;
	dirLightProgram = new engine::ShaderProgram;
	spotLightProgram = new engine::ShaderProgram;
	shadowMapProgram = new engine::ShaderProgram;
	skyboxProgram = new engine::ShaderProgram;
	backgroundProgram = new engine::ShaderProgram;
	screenProgram = new engine::ShaderProgram;
	textProgram = new engine::ShaderProgram;

	configShaders();
	configBuffers();
	configText();
	configLights();
	configScreen();
	configModels();
	configSkybox();

	cam->setPositionCamera(glm::vec3(30, 10, 0));
	cam->setInitialAngle(-90, 0);
}

void kill(void)
{
	delete textProgram;
	delete screenProgram;
	delete backgroundProgram;
	delete skyboxProgram;
	delete shadowMapProgram;
	delete spotLightProgram;
	delete dirLightProgram;
	delete objectProgram;

	delete gBuffer;
	delete text;
	delete screen;
	delete skybox;
	delete heli;
	delete sol;
	delete torch;
	delete sun;
	delete cam;
}

int main(int argc, char **argv)
{
	renderer = new engine::Renderer;

	if (argc < 3)
		renderer->initWindow("Demo OpenGL", 800, 600, GL_FALSE);
	else
		renderer->initWindow("Demo OpenGL", atoi(argv[1]), atoi(argv[2]), GL_FALSE);
	renderer->setDisplayFunc(display);
	renderer->setIdleFunc(idle);
	renderer->setReshapeFunc(reshape);
	renderer->setKeyboardFunc(keyboard);
	renderer->setMouseMoveFunc(mouseMove);

	init();

	renderer->mainLoop();

	kill();

	delete renderer;
	std::cout << "MemState " << engine::Object::getMemoryState() << std::endl;
	engine::Object::saveMemoryInfo("memLost.txt");
	return 0;
}
