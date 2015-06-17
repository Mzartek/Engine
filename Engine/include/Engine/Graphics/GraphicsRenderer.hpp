#ifndef GRAPHICSRENDERER_HEADER
#define GRAPHICSRENDERER_HEADER

#include "../Object.hpp"

#include "Engine/Graphics/Buffer.hpp"
#include "Engine/Graphics/ShaderProgram.hpp"

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

			std::shared_ptr<Buffer> _vertexBuffer;
			std::shared_ptr<Buffer> _colorBuffer;
			GLuint _idVAO;

			std::shared_ptr<ShaderProgram> _windowProgram;

		public:
			static GraphicsRenderer &Instance(void);

		private:
			GraphicsRenderer(void);
			~GraphicsRenderer(void);

		public:
			void initGLWindow(const GLchar *title, GLint width, GLint height, bool fullScreen);
			void setShaderProgram(const std::shared_ptr<ShaderProgram> &windowProgram);

			GLuint getWidth(void) const;
			GLuint getHeight(void) const;
			GLuint getScreenVertexArray(void) const;

			void mainLoop(GameLoop *gameLoop);
			void stopLoop(void);
			void display(GLuint idTexture, const glm::vec4 &color) const;
			void clear(void) const;
		};
	}
}

#endif
