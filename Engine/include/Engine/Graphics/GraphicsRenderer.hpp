#ifndef GRAPHICSRENDERER_HEADER
#define GRAPHICSRENDERER_HEADER

#include "../Object.hpp"

#include "Engine/Graphics/Window.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI GraphicsRenderer
		{
		private:
			GraphicsRenderer(void);
			~GraphicsRenderer(void);

			SDL_GLContext _GLContext;

		public:
			static GraphicsRenderer &Instance(void);

			void setGLContext(const std::shared_ptr<Window> &window);
		};
	}
}

#endif
