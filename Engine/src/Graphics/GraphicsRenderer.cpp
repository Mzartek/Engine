#include <Engine/Graphics/GraphicsRenderer.hpp>

Engine::Graphics::GameLoop::GameLoop(void){}
Engine::Graphics::GameLoop::~GameLoop(void){}

Engine::Graphics::GraphicsRenderer &Engine::Graphics::GraphicsRenderer::Instance(void)
{
	static GraphicsRenderer instance;
	return instance;
}

Engine::Graphics::GraphicsRenderer::GraphicsRenderer(void)
	: _Window(nullptr), _GLContext(nullptr), _stopLoop(false), _width(0), _height(0)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception(SDL_GetError());
	}

	if (TTF_Init() < 0)
	{
		throw std::exception(TTF_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

Engine::Graphics::GraphicsRenderer::~GraphicsRenderer(void)
{
	if (_GLContext) SDL_GL_DeleteContext(_GLContext);
	if (_Window) SDL_DestroyWindow(_Window);
	TTF_Quit();
	SDL_Quit();
}

void Engine::Graphics::GraphicsRenderer::init(const GLchar *title, GLint width, GLint height, bool fullScreen)
{
	Uint32 flags;

	if (_GLContext) SDL_GL_DeleteContext(_GLContext);
	if (_Window) SDL_DestroyWindow(_Window);

	_width = width;
	_height = height;

	if (fullScreen)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	else
		flags = SDL_WINDOW_OPENGL;

	_Window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
	if (_Window == nullptr)
	{
		throw std::exception(SDL_GetError());
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
		throw std::exception(reinterpret_cast<const char *>(glewGetErrorString(err)));
	}
	std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
#endif
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Engine::Graphics::GraphicsRenderer::setState(void) const
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

GLuint Engine::Graphics::GraphicsRenderer::getWidth(void) const
{
	return _width;
}

GLuint Engine::Graphics::GraphicsRenderer::getHeight(void) const
{
	return _height;
}

void Engine::Graphics::GraphicsRenderer::mainLoop(GameLoop *gameLoop)
{
	if (gameLoop == nullptr)
	{
		throw std::invalid_argument("Wrong GameLoop");
	}

	SDL_Event event;
	long long startTime, currentTime, newTime, frameTime;
	long long accumulator = 0;
	long long dt = 16;

	_stopLoop = false;

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
				_stopLoop = true;
				break;
			}
		}

		newTime = SDL_GetTicks() - startTime;
		frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;
		if (accumulator >= dt)
		{
			while (accumulator >= dt)
			{
				gameLoop->state(currentTime);
				accumulator -= dt;
			}
			gameLoop->last_state();
		}

		gameLoop->display(static_cast<GLfloat>(accumulator) / dt);
		SDL_GL_SwapWindow(_Window);
	}
}

void Engine::Graphics::GraphicsRenderer::stopLoop(void)
{
	_stopLoop = true;
}

void Engine::Graphics::GraphicsRenderer::clear(void) const
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