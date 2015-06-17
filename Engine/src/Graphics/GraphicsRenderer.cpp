#include <Engine/Graphics/GraphicsRenderer.hpp>

Engine::Graphics::GameLoop::GameLoop(void){}
Engine::Graphics::GameLoop::~GameLoop(void){}

Engine::Graphics::GraphicsRenderer &Engine::Graphics::GraphicsRenderer::Instance(void)
{
	static GraphicsRenderer instance;
	return instance;
}

Engine::Graphics::GraphicsRenderer::GraphicsRenderer(void)
	: _Window(NULL), _GLContext(NULL), _idVAO(0)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error init SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}

	if (TTF_Init() < 0)
	{
		std::cerr << "Error init SDL_ttf: " << TTF_GetError() << std::endl;
		exit(1);
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
}

Engine::Graphics::GraphicsRenderer::~GraphicsRenderer(void)
{
	if (_idVAO) glDeleteVertexArrays(1, &_idVAO);
	if (_GLContext) SDL_GL_DeleteContext(_GLContext);
	if (_Window) SDL_DestroyWindow(_Window);
	TTF_Quit();
	SDL_Quit();
}

void Engine::Graphics::GraphicsRenderer::initGLWindow(const GLchar *title, GLint width, GLint height, bool fullScreen)
{
	Uint32 flags;

	if (_idVAO) glDeleteVertexArrays(1, &_idVAO);
	if (_GLContext) SDL_GL_DeleteContext(_GLContext);
	if (_Window) SDL_DestroyWindow(_Window);

	_width = width;
	_height = height;

	if (fullScreen)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	else
		flags = SDL_WINDOW_OPENGL;

	_Window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
	if (_Window == NULL)
	{
		std::cerr << "Error while creating Window: " << SDL_GetError() << std::endl;
		exit(1);
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
		exit(1);
	}
	std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
#endif
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

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

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void Engine::Graphics::GraphicsRenderer::setShaderProgram(const std::shared_ptr<ShaderProgram> &windowProgram)
{
	_windowProgram = windowProgram;

	glUseProgram(_windowProgram->getId());
	glUniform1i(glGetUniformLocation(_windowProgram->getId(), "inputTexture"), 0);
}

GLuint Engine::Graphics::GraphicsRenderer::getWidth(void) const
{
	return _width;
}

GLuint Engine::Graphics::GraphicsRenderer::getHeight(void) const
{
	return _height;
}

GLuint Engine::Graphics::GraphicsRenderer::getScreenVertexArray(void) const
{
	return _idVAO;
}

void Engine::Graphics::GraphicsRenderer::mainLoop(GameLoop *gameLoop)
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

		gameLoop->display((GLfloat)accumulator / dt);
		SDL_GL_SwapWindow(_Window);
	}
}

void Engine::Graphics::GraphicsRenderer::stopLoop(void)
{
	_stopLoop = true;
}

void Engine::Graphics::GraphicsRenderer::display(GLuint idTexture, const glm::vec4 &color) const
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