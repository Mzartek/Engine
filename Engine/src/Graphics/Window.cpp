#include <Engine/Graphics/Window.hpp>

Engine::Graphics::GameLoop::GameLoop(void){}
Engine::Graphics::GameLoop::~GameLoop(void){}

Engine::Graphics::Window::Window(const GLchar *title, GLint w, GLint h, GLboolean fullScreen)
	: _width(w), _height(h)
{
	Uint32 flags;

	if (fullScreen == GL_TRUE)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	else
		flags = SDL_WINDOW_OPENGL;

	_Window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
	if (_Window == NULL)
	{
		std::cerr << "Error while creating Window: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

Engine::Graphics::Window::~Window(void)
{
	SDL_DestroyWindow(_Window);
}

GLuint Engine::Graphics::Window::getWidth(void) const
{
	return _width;
}

GLuint Engine::Graphics::Window::getHeight(void) const
{
	return _height;
}

SDL_Window *Engine::Graphics::Window::getWindow(void) const
{
	return _Window;
}

void Engine::Graphics::Window::mainLoop(const std::shared_ptr<GameLoop> &gameLoop)
{
	SDL_Event event;
	long long startTime, currentTime, newTime, frameTime;
	long long accumulator = 0;
	long long dt = 16;

	if (gameLoop == NULL)
	{
		std::cerr << "Wrong GameLoop" << std::endl;
		exit(1);
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

		gameLoop->display((GLfloat)accumulator / dt);
		SDL_GL_SwapWindow(_Window);
	}
}

void Engine::Graphics::Window::stopLoop(void)
{
	_stopLoop = GL_TRUE;
}

void Engine::Graphics::Window::setState(void) const
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

void Engine::Graphics::Window::clear(void) const
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