#ifndef SHADOW_MAP
#define SHADOW_MAP

#include "FrameBuffer.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
	class DLLAPI ShadowMap : public FrameBuffer
	{
	private:
		GLuint _idDepthTexture;
		ShaderProgram *_program;
		GLint _MVPLocation;
		GLint _colorTextureLocation;
		GLint _shadowMapLocation;
	public:
		ShadowMap(void);
		~ShadowMap(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
		GLuint getIdDepthTexture(void) const;
		GLuint getProgramId(void) const;
		GLint getMVPLocation(void) const;
		GLint getColorTextureLocation(void) const;
		GLint getShadowMapLocation(void) const;
		void clear(void) const;
	};
}

#endif
