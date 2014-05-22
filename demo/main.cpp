#include "mainHead.hpp"

GLboolean keyState[256];
Mix_Music *song;
GLfloat sr, sg, sb, sa;

engine::Window *window;
engine::Renderer *renderer;
engine::Camera *cam;
engine::DirLight *sun;
engine::Model *face;
engine::OBJModel *helicopter;
engine::OBJModel *grotor;
engine::OBJModel *protor;
engine::SkyBox *skybox;
engine::Screen *screen;
engine::TextArray *text1;
engine::TextArray *text2;
engine::TextArray *text3;

engine::ShaderProgram *mainProgram;
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
	grotor->matTranslate(0.025f, 0.0f, -0.5f);
	protor->matRotate(angle, x, y, z);
	protor->matTranslate(0.20f, 1.2f, 9.87f);
}

void helicopterRotateRotor(GLfloat angle)
{
	grotor->matRotate(angle, 0, 1, 0);
	protor->matRotate(angle, 1, 0, 0);
}

void helicopterDisplayShadow(engine::Light *l)
{
	helicopter->displayShadow(l);
	grotor->displayShadow(l);
	protor->displayShadow(l);
}

void helicopterDisplay(void)
{
	helicopter->display();
	grotor->display();
	protor->display();
}

void display(void)
{
	sun->position();
	sun->newLoop();
	face->displayShadow(sun);
	helicopterDisplayShadow(sun);

	cam->position();
	renderer->newLoop();
	skybox->display();
	face->display();
	helicopterDisplay();

	screen->display(sr, sg, sb, sa);
	text1->display();
	text2->display();
	text3->display();
}

void reshape(GLuint w, GLuint h)
{
	cam->setPerspective(90.0f, w, h, 0.1f, 2000.0f);
}

void keyboard(GLubyte key, GLboolean state)
{
	keyState[key] = state;

	// if(keyState[MAJ]==GL_TRUE)
	//   cam->setSpeed(0.05f);
	// else
	//   cam->setSpeed(0.25f);

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
	(void)xrel; (void)yrel;
	// cam->mouseMove(xrel, yrel);
}

void init(void)
{
	window = new engine::Window;
	renderer = new engine::Renderer;
	cam = new engine::Camera;
	sun = new engine::DirLight;
	face = new engine::Model;
	helicopter = new engine::OBJModel;
	grotor = new engine::OBJModel;
	protor = new engine::OBJModel;
	skybox = new engine::SkyBox;
	screen = new engine::Screen;
	text1 = new engine::TextArray;
	text2 = new engine::TextArray;
	text3 = new engine::TextArray;
	
	// cam->setPositionCamera(0, 1, 0);
	// cam->setSpeed(0.25f);
}

void initGL(void)
{
	GLfloat vertex[] = { -1000, 0, -1000,
			     0, 0,//
			     0, 1, 0,
			     -1000, 0, 1000,
			     0, 1,//
			     0, 1, 0,
			     1000, 0, 1000,
			     1, 1,//
			     0, 1, 0,
			     1000, 0, -1000,
			     1, 0,//
			     0, 1, 0
	};
	GLuint index[] = { 0, 1, 2, 0, 2, 3 };
	GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 20.0f };
	
	mainProgram = new engine::ShaderProgram;
	shadowProgram = new engine::ShaderProgram;
	skyboxProgram = new engine::ShaderProgram;
	screenProgram = new engine::ShaderProgram;
	textProgram = new engine::ShaderProgram;
	
	mainProgram->loadProgram("shader/demoVert.c", "shader/demoFrag.c");
	shadowProgram->loadProgram("shader/shadowVert.c", "shader/shadowFrag.c");
	skyboxProgram->loadProgram("shader/skyboxVert.c", "shader/skyboxFrag.c");
	screenProgram->loadProgram("shader/screenVert.c", "shader/screenFrag.c");
	textProgram->loadProgram("shader/textVert.c", "shader/textFrag.c");

	text1->config("resources/font/SIXTY.TTF", 100,
		      255, 255, 255,
		      200, 400, 400, 100, textProgram, window);
	text2->config("resources/font/SIXTY.TTF", 100,
		      255, 255, 255,
		      200, 200, 400, 100, textProgram, window);
	text3->config("resources/font/SIXTY.TTF", 50,
		      255, 255, 255,
		      200, 100, 400, 100, textProgram, window);

	renderer->setShaderProgram(mainProgram);
	renderer->setCamera(cam);
	renderer->setDirLight(sun);

	sun->configShadowMap(2048, 2048, shadowProgram);
	sun->setDirection(1, -1, 0);
	sun->setDimension(50, 50, 50);
	sun->setAmbient(mat_ambient[0], mat_ambient[1], mat_ambient[2], mat_ambient[3]);
	sun->setDiffuse(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2], mat_diffuse[3]);
	sun->setSpecular(mat_specular[0], mat_specular[1], mat_specular[2], mat_specular[3]);

	skybox->load("resources/Skybox/rightred2.jpg", "resources/Skybox/leftred2.jpg",
		     "resources/Skybox/topred2.jpg", "resources/Skybox/botred2.jpg",
		     "resources/Skybox/frontred2.jpg", "resources/Skybox/backred2.jpg",
		     100, cam, skyboxProgram);
	skybox->rotate(0, 0, 0, 0);

	face->setRenderer(renderer);
	face->createObject(sizeof vertex, vertex,
			   sizeof index, index,
			   "resources/sand.jpg",
			   mat_ambient, mat_diffuse, mat_specular, mat_shininess);

	helicopter->setRenderer(renderer);
	helicopter->loadObj("resources/UH-60_Blackhawk/corps.obj", 1);
	helicopter->sortObject();

	grotor->setRenderer(renderer);
	grotor->loadObj("resources/UH-60_Blackhawk/grotor.obj");
	grotor->sortObject();

	protor->setRenderer(renderer);
	protor->loadObj("resources/UH-60_Blackhawk/protor.obj", 1);
	protor->sortObject();

	screen->init(screenProgram);
	sr = sg = sb = 0.0f;
	sa = 1.0f;
}

void deleteClass(void)
{
	delete renderer;
	delete cam;
	delete sun;
	delete face;
	delete helicopter;
	delete grotor;
	delete protor;
	delete skybox;
	delete screen;
	delete text1;
	delete text2;
	delete text3;
	
	delete mainProgram;
	delete shadowProgram;
	delete skyboxProgram;
	delete screenProgram;
	delete textProgram;
	
	delete window; // Need to be destroyed at last
}

int main(int argc, char **argv)
{
	init();

	if (argc < 3)
		window->initWindow("Demo", 800, 600);
	else
		window->initWindow("Demo", atoi(argv[1]), atoi(argv[2]));
	window->setDisplayFunc(display);
	window->setIdleFunc(sequence);
	window->setReshapeFunc(reshape);
	window->setKeyboardFunc(keyboard);
	window->setMouseMoveFunc(mouseMove);

	initGL();
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		std::cerr << Mix_GetError() << std::endl;
		return 1;
	}
	song = Mix_LoadMUS("resources/song/song.mp3");
	Mix_PlayMusic(song, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

	window->mainLoop();

	Mix_FreeMusic(song);
	Mix_CloseAudio();

	deleteClass();

	return 0;
}
