#include <Engine/Graphics/Renderer.hpp>

Engine::GameLoop::GameLoop(void){}
Engine::GameLoop::~GameLoop(void){}

Engine::Renderer::Renderer(const GLchar *title, GLint w, GLint h, GLboolean fullScreen)
	: _width(w), _height(h)
{
	Uint32 flags;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error init SDL: " << SDL_GetError() << std::endl;
		abort();
	}

	if (TTF_Init() < -1)
	{
		std::cerr << "Error init SDL_ttf: " << TTF_GetError() << std::endl;
		abort();
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (fullScreen == GL_TRUE)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	else
		flags = SDL_WINDOW_OPENGL;

	_Window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
	if (_Window == NULL)
	{
		std::cerr << "Error while creating Window: " << SDL_GetError() << std::endl;
		abort();
	}
	_GLContext = SDL_GL_CreateContext(_Window);

	SDL_GL_SetSwapInterval(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	glDrawBuffer(GL_BACK);

#ifdef WIN32
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << "Error init GLEW: " << glewGetErrorString(err) << std::endl;
		abort();
	}
	std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
#endif
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

Engine::Renderer::~Renderer(void)
{
	SDL_GL_DeleteContext(_GLContext);
	SDL_DestroyWindow(_Window);
	TTF_Quit();
	SDL_Quit();
}

GLuint Engine::Renderer::getWidth(void) const
{
	return _width;
}

GLuint Engine::Renderer::getHeight(void) const
{
	return _height;
}

SDL_Window *Engine::Renderer::getWindow(void) const
{
	return _Window;
}

void Engine::Renderer::mainLoop(const std::shared_ptr<GameLoop> &gameLoop)
{
	SDL_Event event;
	long long startTime, currentTime, newTime, frameTime;
	long long accumulator = 0;
	long long dt = 16;

	if (gameLoop == NULL)
	{
		std::cerr << "Wrong GameLoop" << std::endl;
		abort();
	}

	_stopLoop = GL_FALSE;

	gameLoop->reshape(_width, _height);

	startTime = SDL_GetTicks();
	currentTime = SDL_GetTicks() - startTime;

	while (!_stopLoop)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_stopLoop = GL_TRUE;
				break;
			}
		}

		newTime = SDL_GetTicks() - startTime;
		frameTime = newTime - currentTime;
		currentTime = newTime;

		for (accumulator += frameTime; accumulator >= dt; accumulator -= dt)
			gameLoop->idle(currentTime);

		gameLoop->display((GLfloat)accumulator / dt);
		SDL_GL_SwapWindow(_Window);
	}
}

void Engine::Renderer::stopLoop(void)
{
	_stopLoop = GL_TRUE;
}

void Engine::Renderer::setState(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

void Engine::Renderer::clear(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0xFF);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
