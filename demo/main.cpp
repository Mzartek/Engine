#include "config.hpp"

GLboolean keyState[256];
GLfloat sr, sg, sb, sa;

engine::Window *window;
engine::FreeCam *cam;
engine::DirLight *sun;
engine::Model *face;
engine::Model *cube1;
engine::Model *cube2;
engine::Model *cube3;
engine::Model *cube4;
engine::Model *heli;
engine::SkyBox *skybox;
engine::Screen *screen;
engine::TextArray *text1;
engine::TextArray *text2;
engine::TextArray *text3;
engine::GBuffer *gBuffer;

engine::ShaderProgram *objectProgram;
engine::ShaderProgram *lightProgram;
engine::ShaderProgram *shadowProgram;
engine::ShaderProgram *skyboxProgram;
engine::ShaderProgram *screenProgram;
engine::ShaderProgram *textProgram;

void display(void)
{
	cam->position();
	sun->position();

	// Shadow Pass
	sun->clear();
	face->displayShadow(sun);
	cube1->displayShadow(sun);
	cube2->displayShadow(sun);
	cube3->displayShadow(sun);
	cube4->displayShadow(sun);
	heli->displayShadow(sun);

	// GLObject Pass
	gBuffer->clear();
	skybox->display(gBuffer, cam);
	face->display(gBuffer, cam);
	cube1->display(gBuffer, cam);
	cube2->display(gBuffer, cam);
	cube3->display(gBuffer, cam);
	cube4->display(gBuffer, cam);
	heli->display(gBuffer, cam);

	// Light Pass
	sun->display(gBuffer, cam);

	// Screen
	window->clear();
	screen->display(window, gBuffer, sr, sg, sb, sa);

	// Text
	//text1->display();
	//text2->display();
	//text3->display();
}

void idle(void)
{
	sun->setPosition(heli->getPosition().x, heli->getPosition().y, heli->getPosition().z);
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
			window->stopLoop();
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
	face = new engine::Model;
	cube1 = new engine::Model;
	cube2 = new engine::Model;
	cube3 = new engine::Model;
	cube4 = new engine::Model;
	heli = new engine::Model;
	skybox = new engine::SkyBox;
	screen = new engine::Screen;
	text1 = new engine::TextArray;
	text2 = new engine::TextArray;
	text3 = new engine::TextArray;
	gBuffer = new engine::GBuffer;

	objectProgram = new engine::ShaderProgram;
	lightProgram = new engine::ShaderProgram;
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

	cam->setPositionCamera(0, 1, 0);
	cam->setSpeed(0.25f);
}

void kill(void)
{
	delete textProgram;
	delete screenProgram;
	delete skyboxProgram;
	delete shadowProgram;
	delete lightProgram;
	delete objectProgram;

	delete gBuffer;
	delete text3;
	delete text2;
	delete text1;
	delete screen;
	delete skybox;
	delete heli;
	delete cube4;
	delete cube3;
	delete cube2;
	delete cube1;
	delete face;
	delete sun;
	delete cam;
}

int main(int argc, char **argv)
{
	window = new engine::Window;

	if (argc < 3)
		window->initWindow("Demo", 1680, 1050, GL_TRUE);
	else
		window->initWindow("Demo", atoi(argv[1]), atoi(argv[2]), GL_FALSE);
	window->setDisplayFunc(display);
	window->setIdleFunc(idle);
	window->setReshapeFunc(reshape);
	window->setKeyboardFunc(keyboard);
	window->setMouseMoveFunc(mouseMove);

	init();

	window->mainLoop();

	kill();

	delete window;
	std::cout << "MemState " << engine::Object::getMemoryState() << std::endl;
	engine::Object::saveMemoryInfo("memLost.txt");
	return 0;
}
