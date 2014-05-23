#ifndef GBUFFER
#define GBUFFER

#include "FrameBuffer.hpp"

namespace engine
{
	class GBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[2];
		GLuint _idDepthTexture;
	public:
		GLint MVPLocation;
		GBuffer(void);
		~GBuffer(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
		GLuint getIdTexture(GLuint num);
		GLuint getIdDepthTexture(void);
	};
}

#endif
