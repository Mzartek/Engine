#ifndef GBUFFER
#define GBUFFER

#include "FrameBuffer.hpp"

namespace engine
{
	class GBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[3];
		GLuint _idDepthTexture;
		GLint _MVPLocation;
		GLint _textureLocation;
	public:
		GBuffer(void);
		~GBuffer(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
		GLuint getIdTexture(GLuint num) const;
		GLuint getIdDepthTexture(void) const;
		GLint getMVPLocation(void) const;
		GLint getTextureLocation(void) const;
	};
}

#endif
