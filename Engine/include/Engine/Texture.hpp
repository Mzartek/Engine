#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include "Object.hpp"

namespace Engine
{
	class DLLAPI Texture : public Object
	{
	private:
		GLuint _idTexture;
	public:
		Texture(void);
		~Texture(void);
		GLuint getId(void);
		void load2DTextureFromFile(const GLchar *path);
		void load2DTextureFromSDL_Surface(const SDL_Surface *surface);
		void loadCubeTextureFromFiles(
			const GLchar *posx, const GLchar *negx,
			const GLchar *posy, const GLchar *negy,
			const GLchar *posz, const GLchar *negz);
	};
}

#endif
