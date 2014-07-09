#include <Engine/Window.hpp>

engine::Window::Window(void)
{
	_display = NULL;
	_idle = NULL;
	_reshape = NULL;
	_keyboard = NULL;
	_mouseMove = NULL;
}

engine::Window::~Window(void)
{
	TTF_Quit();
	SDL_Quit();
}

void engine::Window::initWindow(const std::string title, GLint const &w, GLint const &h, GLboolean fullScreen)
{
	Uint32 flags;
	
	_exit = false;
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
  
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetSwapInterval(1);

	if(fullScreen == GL_TRUE)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	else
		flags = SDL_WINDOW_OPENGL;
	_idWindow = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
  
	if(!_idWindow)
	{
		std::cerr << "Can't set video mode: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
  
	_idGLContext = SDL_GL_CreateContext(_idWindow);

#ifdef WIN32
	if(glewInit())
	{
		std::cerr << "Error init GLEW" << std::endl;
		exit(1);
	}
#endif
  
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void engine::Window::setDisplayFunc(void (*f) (void))
{
	_display = f;
}

void engine::Window::setIdleFunc(void (*f) (void))
{
	_idle = f;
}

void engine::Window::setReshapeFunc(void (*f) (GLuint, GLuint))
{
	_reshape = f;
}

void engine::Window::setKeyboardFunc(void (*f) (GLubyte, GLboolean))
{
	_keyboard = f;
}

void engine::Window::setMouseMoveFunc(void (*f) (GLint, GLint))
{
	_mouseMove = f;
}

GLuint engine::Window::getWidth(void)
{
	return _width;
}

GLuint engine::Window::getHeight(void)
{
	return _height;
}

SDL_Window *engine::Window::getId(void)
{
	return _idWindow;
}

void engine::Window::mainLoop(void)
{
	SDL_Event event;
	
	SDL_SetRelativeMouseMode(SDL_TRUE);
	_reshape(_width, _height);
	while(!_exit)
	{
		while(SDL_PollEvent(&event))
			switch(event.type)
			{
			case SDL_QUIT:
				_exit = true;
				break;
			case SDL_KEYDOWN:
				if(_keyboard)
					_keyboard((GLubyte)event.key.keysym.scancode, (GLubyte)event.key.state);
				break;
			case SDL_KEYUP:
				if(_keyboard)
					_keyboard((GLubyte)event.key.keysym.scancode, (GLubyte)event.key.state);
				break;
			case SDL_MOUSEMOTION:
				if(_mouseMove)
					_mouseMove(event.motion.xrel, event.motion.yrel);
				break;
			}
		if(_idle)
			_idle();
		if(_display)
			_display();
		
		SDL_GL_SwapWindow(_idWindow);
	}

	SDL_GL_DeleteContext(_idGLContext);
	SDL_DestroyWindow(_idWindow);
}

void engine::Window::stop(void)
{
	_exit=true;
}

void engine::Window::clear(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, _width, _height);
}
