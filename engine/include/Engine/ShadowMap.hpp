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
		// Do not delete it
		ShaderProgram *_program;
		// Location or Index
		GLint _MVPLocation;
		GLint _colorTextureLocation;
	public:
		ShadowMap(void);
		~ShadowMap(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
		GLuint getIdDepthTexture(void) const;
		GLuint getProgramId(void) const;
		GLint getMVPLocation(void) const;
		GLint getColorTextureLocation(void) const;
		void clear(void) const;
	};
}

#endif
