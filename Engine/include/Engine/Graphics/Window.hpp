#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "../Object.hpp"
#include "Buffer.hpp"
#include "ShaderProgram.hpp"

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

		class DLLAPI Window : public Object
		{
		private:
			GLboolean _stopLoop;
			GLuint _width;
			GLuint _height;
			SDL_Window *_Window;

			std::shared_ptr<ShaderProgram> _windowProgram;
			std::shared_ptr<Buffer> _vertexBuffer;
			std::shared_ptr<Buffer> _colorBuffer;
			GLuint _idVAO;

		public:
			Window(const GLchar *title, GLint w, GLint h, GLboolean fullScreen, const std::shared_ptr<ShaderProgram> &windowProgram);
			~Window(void);

			GLuint getWidth(void) const;
			GLuint getHeight(void) const;
			SDL_Window *getWindow(void) const;
			void mainLoop(GameLoop *gameLoop);
			void stopLoop(void);
			void display(GLuint idTexture, const glm::vec4 &color) const;
			void clear(void) const;
		};
	}
}

#endif