#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include "../Object.hpp"

namespace Engine
{
	enum TextureType { TEXTURE_2D_TYPE, TEXTURE_CUBE_TYPE };

	class DLLAPI Texture : public Object
	{
	protected:
		GLuint _idTexture;

	public:
		Texture(void);
		~Texture(void);
		GLuint getId(void) const;
		virtual TextureType getType(void) const = 0;
	};
}

#endif
