#ifndef WINDOW
#define WINDOW

#include "GL.hpp"

namespace engine
{
  class Window
  {
  private:
    bool _exit;
    unsigned _width;
    unsigned _height;
    SDL_Window *_idWindow;
    SDL_GLContext _idGLContext;
    void (*_display) (void);
    void (*_idle) (void);
    void (*_reshape) (int, int);
    void (*_keyboard) (unsigned char, bool);
    void (*_mouseMove) (int, int);
  public:
    Window(void);
    ~Window(void);
    void initWindow(const std::string title, int const &w, int const &h);
    void setDisplayFunc(void (*f) (void));
    void setIdleFunc(void (*f) (void));
    void setReshapeFunc(void (*f) (int, int));
    void setKeyboardFunc(void (*f) (unsigned char, bool));
    void setMouseMoveFunc(void (*f) (int, int));
    unsigned int getWidth(void);
    unsigned int getHeight(void);
    void mainLoop(void);
    void stop(void);
  };
}

#endif
