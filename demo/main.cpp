#include "config.hpp"

GLboolean keyState[256];
GLfloat sr, sg, sb, sa;

engine::Window *window;
engine::FreeCam *cam;
engine::DirLight *sun;
engine::Model *face;
engine::OBJModel *cube1;
engine::Model *cube2;
engine::Model *cube3;
engine::Model *cube4;
engine::Model *helicopter;
engine::Model *grotor;
engine::Model *protor;
engine::SkyBox *skybox;
engine::Screen *screen;
engine::TextArray *text1;
engine::TextArray *text2;
engine::TextArray *text3;
engine::GBuffer *gBuffer;
engine::LBuffer *lBuffer;

engine::ShaderProgram *objectProgram;
engine::ShaderProgram *lightProgram;
engine::ShaderProgram *shadowProgram;
engine::ShaderProgram *skyboxProgram;
engine::ShaderProgram *screenProgram;
engine::ShaderProgram *textProgram;

void helicopterMatrixIdentity(void)
{
	helicopter->matIdentity();
	grotor->matIdentity();
	protor->matIdentity();
}

void helicopterMatrixScale(GLfloat x, GLfloat y, GLfloat z)
{
	helicopter->matScale(x, y, z);
	grotor->matScale(x, y, z);
	protor->matScale(x, y, z);
}

void helicopterMatrixTranslate(GLfloat x, GLfloat y, GLfloat z)
{
	helicopter->matTranslate(x, y, z);
	grotor->matTranslate(x, y, z);
	protor->matTranslate(x, y, z);
}

void helicopterMatrixRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	helicopter->matRotate(angle, x, y, z);
	grotor->matRotate(angle, x, y, z);
	protor->matRotate(angle, x, y, z);
}

void helicopterRotateRotor(GLfloat angle)
{
	grotor->matTranslate(0.050f, 0.0f, -1.0f);
	grotor->matRotate(angle, 0, 1, 0);
	protor->matTranslate(0.40f, 2.4f, 19.74f);
	protor->matRotate(angle, 1, 0, 0);
}

void helicopterDisplayShadow(engine::Light *l)
{
	helicopter->displayShadow(l);
	grotor->displayShadow(l);
	protor->displayShadow(l);
}

void helicopterDisplay(engine::GBuffer *g, engine::Camera *c)
{
	helicopter->display(g, c);
	grotor->display(g, c);
	protor->display(g, c);
}

/*void helicopterDisplay(engine::Window *w, engine::Camera *c, engine::LBuffer *l)
{
	helicopter->display(w, c, l);
	grotor->display(w, c, l);
	protor->display(w, c, l);
}*/

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
	helicopterDisplayShadow(sun);

	// GBuffer
	gBuffer->clear();
	face->display(gBuffer, cam);
	cube1->display(gBuffer, cam);
	cube2->display(gBuffer, cam);
	cube3->display(gBuffer, cam);
	cube4->display(gBuffer, cam);
	helicopterDisplay(gBuffer, cam);

	// LBuffer
	lBuffer->clear();
	sun->display(lBuffer, gBuffer, cam);

	// Nothing
	window->clear();
	//skybox->display(cam);

	screen->display(gBuffer, lBuffer, sr, sg, sb, sa);

	text1->display();
	// text2->display();
	// text3->display();
}

void idle(void)
{
	sun->setPosition(helicopter->getPosition().x, helicopter->getPosition().y, helicopter->getPosition().z);
	cam->keyboardMove(keyState[26], keyState[22], keyState[4], keyState[7]);
}

void reshape(GLuint w, GLuint h)
{
	cam->setPerspective(90.0f, w, h, 0.001f, 2000.0f);
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
			window->stop();
			break;
		}
}

void mouseMove(GLint xrel, GLint yrel)
{
	cam->mouseMove(xrel, yrel);
}

void init(void)
{
	window = new engine::Window;
	cam = new engine::FreeCam;
	sun = new engine::DirLight;
	face = new engine::Model;
	cube1 = new engine::OBJModel;
	cube2 = new engine::Model;
	cube3 = new engine::Model;
	cube4 = new engine::Model;
	helicopter = new engine::Model;
	grotor = new engine::Model;
	protor = new engine::Model;
	skybox = new engine::SkyBox;
	screen = new engine::Screen;
	text1 = new engine::TextArray;
	text2 = new engine::TextArray;
	text3 = new engine::TextArray;
	gBuffer = new engine::GBuffer;
	lBuffer = new engine::LBuffer;

	cam->setPositionCamera(0, 1, 0);
	cam->setSpeed(0.25f);

    helicopterMatrixIdentity();
	helicopterMatrixTranslate(0.0f, 6.0f, 0.0f);
	helicopterRotateRotor(0.0f);
	helicopterMatrixScale(2, 2, 2);
}

void initGL(void)
{
	configShaders();
	configBuffers();
	configText();
	configLights();
	configScreen();
	configModels();
	configSkybox();
}

void deleteClass(void)
{
	delete textProgram;
	delete screenProgram;
	delete skyboxProgram;
	delete shadowProgram;
	delete lightProgram;
	delete objectProgram;

	delete lBuffer;
	delete gBuffer;
	delete text3;
	delete text2;
	delete text1;
	delete screen;
	delete skybox;
	delete protor;
	delete grotor;
	delete helicopter;
	delete cube4;
	delete cube3;
	delete cube2;
	delete cube1;
	delete face;
	delete sun;
	delete cam;
	delete window; // Need to be destroyed at last
}

int main(int argc, char **argv)
{
	init();

	if (argc < 3)
		window->initWindow("Demo", 1680, 1050, GL_TRUE);
	else
		window->initWindow("Demo", atoi(argv[1]), atoi(argv[2]), GL_FALSE);
	window->setDisplayFunc(display);
	window->setIdleFunc(idle);
	window->setReshapeFunc(reshape);
	window->setKeyboardFunc(keyboard);
	window->setMouseMoveFunc(mouseMove);

	initGL();

	window->mainLoop();

	deleteClass();

	return 0;
}
