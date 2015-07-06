#ifndef GRAPHICSRENDERER_HEADER
#define GRAPHICSRENDERER_HEADER

#include "../Object.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI GameLoop : public Object
		{
		public:
			GameLoop(void);
			~GameLoop(void);
			virtual void display(GLfloat state) = 0;
			virtual void state(long long time) = 0;
			virtual void last_state(void) = 0;
			virtual void reshape(GLuint w, GLuint h) = 0;
		};

		class DLLAPI GraphicsRenderer
		{
		private:
			SDL_Window *_Window;
			SDL_GLContext _GLContext;

			bool _stopLoop;
			GLuint _width;
			GLuint _height;

		public:
			static GraphicsRenderer &Instance(void);

		private:
			GraphicsRenderer(void);
			~GraphicsRenderer(void);

		public:
			void init(const GLchar *title, GLint width, GLint height, bool fullScreen);

			void setState(void) const;

			GLuint getWidth(void) const;
			GLuint getHeight(void) const;

			void mainLoop(GameLoop *gameLoop);
			void stopLoop(void);
			void clear(void) const;
		};
	}
}

#endif
