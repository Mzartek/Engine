#ifndef SHADOW_MAP
#define SHADOW_MAP

#include "FrameBuffer.hpp"

namespace Engine
{
	class DLLAPI ShadowMap : public FrameBuffer
	{
	private:
		GLuint _idDepthTexture;
	public:
		ShadowMap(void);
		~ShadowMap(void);
		void config(const GLuint &width, const GLuint &height);
		GLuint getIdDepthTexture(void) const;
		void setState(void) const;
		void clear(void) const;
	};
}

#endif
