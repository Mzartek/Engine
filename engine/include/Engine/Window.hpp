#ifndef WINDOW
#define WINDOW

#include "GLHead.hpp"

namespace engine
{
  class DLLAPI Window
  {
  private:
    GLboolean _exit;
    GLuint _width;
    GLuint _height;
    SDL_Window *_idWindow;
    SDL_GLContext _idGLContext;
    void (*_display) (void);
    void (*_idle) (void);
    void (*_reshape) (GLuint, GLuint);
    void (*_keyboard) (GLubyte, GLboolean);
    void (*_mouseMove) (GLint, GLint);
  public:
    Window(void);
    ~Window(void);
    void initWindow(const std::string title, GLint const &w, GLint const &h);
    void setDisplayFunc(void (*f) (void));
    void setIdleFunc(void (*f) (void));
    void setReshapeFunc(void (*f) (GLuint, GLuint));
    void setKeyboardFunc(void (*f) (GLubyte, GLboolean));
    void setMouseMoveFunc(void (*f) (GLint, GLint));
    GLuint getWidth(void);
    GLuint getHeight(void);
    void mainLoop(void);
    void stop(void);
  };
}

#endif
