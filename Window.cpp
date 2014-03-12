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
}

void engine::Window::initWindow(char const *title, int const &w, int const &h)
{
  _exit = false;
  _Width = w;
  _Height = h;
  
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "Error init SDL: " << SDL_GetError() << std::endl;
      SDL_Quit();
      exit(1);
    }
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetSwapInterval(1);
  
  _idWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _Width, _Height, SDL_WINDOW_OPENGL);
  
  if(!_idWindow)
    {
      std::cerr << "Can't set video mode: " << SDL_GetError() << std::endl;
      SDL_Quit();
      exit(1);
    }
  
  _idGLContext = SDL_GL_CreateContext(_idWindow);
  
  if(glewInit())
    {
      std::cerr << "Error init GLEW" << std::endl;
      exit(1);
    }
}

void engine::Window::setDisplayFunc(void (*f) (void))
{
  _display = f;
}

void engine::Window::setIdleFunc(void (*f) (void))
{
  _idle = f;
}

void engine::Window::setReshapeFunc(void (*f) (int, int))
{
  _reshape = f;
}

void engine::Window::setKeyboardFunc(void (*f) (unsigned char, bool))
{
  _keyboard = f;
}

void engine::Window::setMouseMoveFunc(void (*f) (int, int))
{
  _mouseMove = f;
}

void engine::Window::mainLoop(void)
{
  SDL_Event event;
  SDL_SetRelativeMouseMode(SDL_TRUE);
  if(_reshape)
    _reshape(_Width, _Height);
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
	      _keyboard(event.key.keysym.scancode, event.key.state);
	    break;
	  case SDL_KEYUP:
	    if(_keyboard)
	      _keyboard(event.key.keysym.scancode, event.key.state);
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
  SDL_Quit();
}

void engine::Window::stop(void)
{
  _exit=true;
}
