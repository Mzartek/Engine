#ifndef WINDOW
#define WINDOW

#include "GL.hpp"

namespace engine
{
  class Window
  {
  private:
    bool _exit;
    int _Width;
    int _Height;
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
    void initWindow(char const *title, int const &w, int const &h);
    void setDisplayFunc(void (*f) (void));
    void setIdleFunc(void (*f) (void));
    void setReshapeFunc(void (*f) (int, int));
    void setKeyboardFunc(void (*f) (unsigned char, bool));
    void setMouseMoveFunc(void (*f) (int, int));
    void mainLoop(void);
    void stop(void);
  };
}

#endif
