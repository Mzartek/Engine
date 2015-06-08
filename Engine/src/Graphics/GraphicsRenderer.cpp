#include <Engine/Graphics/GraphicsRenderer.hpp>

Engine::Graphics::GraphicsRenderer &Engine::Graphics::GraphicsRenderer::Instance(void)
{
	static GraphicsRenderer instance;
	return instance;
}

Engine::Graphics::GraphicsRenderer::GraphicsRenderer(void)
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
	SDL_GL_DeleteContext(_GLContext);
	TTF_Quit();
	SDL_Quit();
}

void Engine::Graphics::GraphicsRenderer::setGLContext(const std::shared_ptr<Window> &window)
{
	static bool first = true;
	if (first)
	{
		_GLContext = SDL_GL_CreateContext(window->getWindow());

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

		SDL_GL_SetSwapInterval(0);
		SDL_SetRelativeMouseMode(SDL_TRUE);

		glDrawBuffer(GL_BACK);

		first = false;
	}
	else if (SDL_GL_MakeCurrent(window->getWindow(), _GLContext) < 0)
	{
		std::cerr << "Error while setting context" << std::endl;
		exit(1);
	}
}