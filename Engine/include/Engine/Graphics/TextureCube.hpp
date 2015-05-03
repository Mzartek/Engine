#ifndef TEXTURECUBE_HEADER
#define TEXTURECUBE_HEADER

#include "Texture.hpp"

namespace Engine
{
	class DLLAPI TextureCube : public Texture
	{
	public:
		TextureCube(void);
		~TextureCube(void);
		TextureType getType(void) const;

		void loadFromFiles(
			const GLchar *posx, const GLchar *negx,
			const GLchar *posy, const GLchar *negy,
			const GLchar *posz, const GLchar *negz);
	};
}

#endif