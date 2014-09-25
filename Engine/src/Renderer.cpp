#include <Engine/Renderer.hpp>

engine::Renderer::Renderer(void)
	: _idWindow(NULL), _idGLContext(NULL),
	_display(NULL), _idle(NULL), _reshape(NULL)
{
}

engine::Renderer::~Renderer(void)
{
	TTF_Quit();
	SDL_Quit();
}

void engine::Renderer::initWindow(const GLchar *title, const GLint &w, const GLint &h, const GLboolean &fullScreen)
{
	Uint32 flags;

	_width = w;
	_height = h;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error init SDL: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	if (TTF_Init() < -1)
	{
		std::cerr << "Error init SDL_ttf " << TTF_GetError() << std::endl;
		TTF_Quit();
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if(fullScreen == GL_TRUE)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	else
		flags = SDL_WINDOW_OPENGL;

	_idWindow = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
	if (_idWindow == NULL)
	{
		std::cerr << "Error while creating Window: " << SDL_GetError();
		exit(1);
	}
	_idGLContext = SDL_GL_CreateContext(_idWindow);
	if (_idGLContext == NULL)
	{
		std::cerr << "Error while creating Context: " << SDL_GetError();
		exit(1);
	}

	SDL_GL_SetSwapInterval(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

#ifdef WIN32
	if(glewInit())
	{
		std::cerr << "Error init GLEW" << std::endl;
		exit(1);
	}
#endif

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void engine::Renderer::setDisplayFunc(void (*f) (void))
{
	_display = f;
}

void engine::Renderer::setIdleFunc(void (*f) (void))
{
	_idle = f;
}

void engine::Renderer::setReshapeFunc(void (*f) (GLuint, GLuint))
{
	_reshape = f;
}

GLuint engine::Renderer::getWidth(void)
{
	return _width;
}

GLuint engine::Renderer::getHeight(void)
{
	return _height;
}

SDL_Window *engine::Renderer::getId(void)
{
	return _idWindow;
}

void engine::Renderer::mainLoop(void)
{
	SDL_Event event;
	long long lastTime, limit = 1000 / 60;

	if (!_reshape || !_idle || !_display)
	{
		std::cerr << "You need to set the Reshape, Idle and Display Function before" << std::endl;
		exit(1);
	}

	_stopLoop = false;
	_reshape(_width, _height);
	lastTime = SDL_GetTicks();
	while (!_stopLoop)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_stopLoop = true;
				break;
			}
		}
		if ((SDL_GetTicks() - lastTime) > limit)
		{
			_idle();
			lastTime = SDL_GetTicks();
		}
		_display();
		SDL_GL_SwapWindow(_idWindow); 
	}
}

void engine::Renderer::stopLoop(void)
{
	_stopLoop = true;
}

void engine::Renderer::setState(void) const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glViewport(0, 0, _width, _height);
	glDepthRange(0.0, 1.0);
}

void engine::Renderer::clear(void) const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0xFF);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}