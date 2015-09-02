#ifndef TEXTURE2D_HEADER
#define TEXTURE2D_HEADER

#include "Texture.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI Texture2D : public Texture
		{
		public:
			Texture2D(void);
			~Texture2D(void);
			TextureType getType(void) const;

			void loadFromFile(const GLchar *path);
			void loadFromSDL_Surface(const SDL_Surface *surface);
		};
	}
}

#endif