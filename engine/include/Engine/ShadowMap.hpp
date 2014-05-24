#ifndef SHADOW_MAP
#define SHADOW_MAP

#include "FrameBuffer.hpp"

namespace engine
{
	class DLLAPI ShadowMap : public FrameBuffer
	{
	private:
		GLuint _idDepthTexture;
		GLint _MVPLocation;
	public:
		ShadowMap(void);
		~ShadowMap(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
		GLuint getIdDepthTexture(void) const;
		GLint getMVPLocation(void) const;
	};
}

#endif
