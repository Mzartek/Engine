#ifndef GBUFFER
#define GBUFFER

#include "FrameBuffer.hpp"
#include "Window.hpp"

#define GBUF_NUM_TEX 3
#define GBUF_POSITION 0
#define GBUF_NORMAL 1
#define GBUF_MATERIAL 2

namespace engine
{
	class DLLAPI GBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[GBUF_NUM_TEX];
		GLuint _idDepthRender;
	public:
		GLenum colorAttachment[GBUF_NUM_TEX];
		GBuffer(void);
		~GBuffer(void);
		void config(const GLuint &width, const GLuint &height);
		GLuint getIdTexture(GLuint num) const;
		GLuint getIdDepthRender(void) const;
		void display(Window *w, GLuint buf) const;
	};
}

#endif
