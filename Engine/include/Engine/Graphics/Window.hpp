#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "../Object.hpp"

namespace Engine
{
	class DLLAPI GameLoop : public Object
	{
	public:
		GameLoop(void);
		~GameLoop(void);
		virtual void display(GLfloat state) = 0;
		virtual void idle(long long time) = 0;
		virtual void reshape(GLuint w, GLuint h) = 0;
	};

	class DLLAPI Window : public Object
	{
	private:
		GLboolean _stopLoop;
		GLuint _width;
		GLuint _height;
		SDL_Window *_Window;

	public:
		Window(const GLchar *title, GLint w, GLint h, GLboolean fullScreen);
		~Window(void);

		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		SDL_Window *getWindow(void) const;
		void mainLoop(const std::shared_ptr<GameLoop> &gameLoop);
		void stopLoop(void);
		void setState(void) const;
		void clear(void) const;
	};
}

#endif