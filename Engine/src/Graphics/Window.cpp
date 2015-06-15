#include <Engine/Graphics/Window.hpp>

Engine::Graphics::GameLoop::GameLoop(void){}
Engine::Graphics::GameLoop::~GameLoop(void){}

Engine::Graphics::Window::Window(const GLchar *title, GLint w, GLint h, GLboolean fullScreen, const std::shared_ptr<ShaderProgram> &windowProgram)
		: _width(w), _height(h), _windowProgram(windowProgram)
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

		_vertexBuffer = std::shared_ptr<Buffer>(new Buffer);
		_colorBuffer = std::shared_ptr<Buffer>(new Buffer);

		GLfloat vertex[] = {
				-1, -1,
				0, 0,

				1, -1,
				1, 0,

				-1, 1,
				0, 1,

				1, 1,
				1, 1,
		};
		_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);
		_colorBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::vec4), GL_DYNAMIC_DRAW);

		glUseProgram(_windowProgram->getId());
		glUniform1i(glGetUniformLocation(_windowProgram->getId(), "inputTexture"), 0);

		glGenVertexArrays(1, &_idVAO);
		glBindVertexArray(_idVAO);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));
		glBindVertexArray(0);
}

Engine::Graphics::Window::~Window(void)
{
		SDL_DestroyWindow(_Window);
		glDeleteVertexArrays(1, &_idVAO);
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

void Engine::Graphics::Window::mainLoop(GameLoop *gameLoop)
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

void Engine::Graphics::Window::display(GLuint idTexture, const glm::vec4 &color) const
{
		// State
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

		// Draw
		glUseProgram(_windowProgram->getId());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, idTexture);

		_colorBuffer->updateStoreMap(glm::value_ptr(color));
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _colorBuffer->getId());

		glBindVertexArray(_idVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
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