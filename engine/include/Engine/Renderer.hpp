#ifndef RENDERER
#define RENDERER

#include "Object.hpp"

namespace engine
{
	class DLLAPI Renderer : public Object
	{
	private:
		GLboolean _stopLoop;
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
		Renderer(void);
		~Renderer(void);
		void initWindow(const GLchar *title, const GLint &w, const GLint &h, const GLboolean &fullScreen);
		void setDisplayFunc(void (*f) (void));
		void setIdleFunc(void (*f) (void));
		void setReshapeFunc(void (*f) (GLuint, GLuint));
		void setKeyboardFunc(void (*f) (GLubyte, GLboolean));
		void setMouseMoveFunc(void (*f) (GLint, GLint));
		GLuint getWidth(void);
		GLuint getHeight(void);
		SDL_Window *getId(void);
		void mainLoop(void);
		void stopLoop(void);
		void clear(void);
	};
}

#endif
