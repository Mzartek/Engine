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
engine::TextArray *text1;
engine::TextArray *text2;
engine::TextArray *text3;
engine::GBuffer *gBuffer;

engine::ShaderProgram *objectProgram;
engine::ShaderProgram *dirLightProgram;
engine::ShaderProgram *spotLightProgram;
engine::ShaderProgram *shadowProgram;
engine::ShaderProgram *skyboxProgram;
engine::ShaderProgram *screenProgram;
engine::ShaderProgram *textProgram;

void display(void)
{
	cam->position();
	sun->position(heli->getPosition(), 25);
	torch->position();

	// Shadow Pass
	/*sun->clear();
	sol->displayShadow(sun);
	heli->displayShadow(sun);*/
	torch->clear();
	sol->displayShadow(torch);
	heli->displayShadow(torch);

	// GLObject Pass
	gBuffer->clear();
	skybox->display(gBuffer, cam);
	sol->display(gBuffer, cam);
	heli->display(gBuffer, cam);

	// Light Pass
	//sun->display(gBuffer, cam);
	torch->display(gBuffer,cam);

	// Screen
	renderer->clear();
	screen->display(gBuffer, 1.0, 1.0, 1.0, 1.0);

	// Text
	//text1->display();
	//text2->display();
	//text3->display();
}

void idle(void)
{
	cam->keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);

	heli->matRotate(0.1f, 0, 1, 0);
}

void reshape(GLuint w, GLuint h)
{
	cam->setPerspective(90.0f, w, h, 0.1f, 1000.f);
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
	text1 = new engine::TextArray;
	text2 = new engine::TextArray;
	text3 = new engine::TextArray;
	gBuffer = new engine::GBuffer;

	objectProgram = new engine::ShaderProgram;
	dirLightProgram = new engine::ShaderProgram;
	spotLightProgram = new engine::ShaderProgram;
	shadowProgram = new engine::ShaderProgram;
	skyboxProgram = new engine::ShaderProgram;
	screenProgram = new engine::ShaderProgram;
	textProgram = new engine::ShaderProgram;

	configShaders();
	configBuffers();
	configText();
	configLights();
	configScreen();
	configModels();
	configSkybox();

	cam->setPositionCamera(30, 10, 0);
	cam->setInitialAngle(-90, 0);
}

void kill(void)
{
	delete textProgram;
	delete screenProgram;
	delete skyboxProgram;
	delete shadowProgram;
	delete spotLightProgram;
	delete dirLightProgram;
	delete objectProgram;

	delete gBuffer;
	delete text3;
	delete text2;
	delete text1;
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
