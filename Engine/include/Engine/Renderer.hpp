#ifndef RENDERER
#define RENDERER

#include "Object.hpp"

namespace Engine
{
	class DLLAPI Renderer : public Object
	{
	private:
		GLboolean _stopLoop;
		GLuint _width;
		GLuint _height;
		SDL_Window *_idWindow;
		SDL_GLContext _idGLContext;
		void(*_display) (GLfloat);
		void (*_idle) (void);
		void (*_reshape) (GLuint, GLuint);
	public:
		Renderer(void);
		~Renderer(void);
		void initWindow(const GLchar *title, const GLint &w, const GLint &h, const GLboolean &fullScreen);
		void setDisplayFunc(void(*f) (GLfloat));
		void setIdleFunc(void (*f) (void));
		void setReshapeFunc(void (*f) (GLuint, GLuint));
		GLuint getWidth(void);
		GLuint getHeight(void);
		SDL_Window *getId(void);
		void mainLoop(void);
		void stopLoop(void);
		void setState(void) const;
		void clear(void) const;
	};
}

#endif
