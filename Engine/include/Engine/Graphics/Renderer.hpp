#ifndef RENDERER_HEADER
#define RENDERER_HEADER

#include "../Object.hpp"

#include "Engine/Graphics/Window.hpp"

namespace Engine
{
	class DLLAPI Renderer : public Object
	{
	private:
		static Renderer _instance;
		Renderer(void);
		~Renderer(void);
		

		SDL_GLContext _GLContext;

	public:
		static Renderer &Instance(void);

		void init(void);
		void setGLContext(const std::shared_ptr<Window> &window);
	};
}

#endif
