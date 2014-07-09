#ifndef GBUFFER
#define GBUFFER

#include "FrameBuffer.hpp"
#include "Window.hpp"

#define GBUF_NUM_TEX 3
#define GBUF_POSITION 0
#define GBUF_NORMAL 1
#define GBUF_DIFFUSE 2

namespace engine
{
	class DLLAPI GBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[GBUF_NUM_TEX];
		GLuint _idDepthRender;
		GLint _MVPLocation;
		GLint _modelMatrixLocation;
		GLint _normalMatrixLocation;
		GLint _shininessLocation;
		GLint _colorTextureLocation;
	public:
		GBuffer(void);
		~GBuffer(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program, GLboolean withColor);
		GLuint getIdTexture(GLuint num) const;
		GLuint getIdDepthRender(void) const;
		GLint getMVPLocation(void) const;
		GLint getModelMatrixLocation(void) const;
		GLint getNormalMatrixLocation(void) const;
		GLint getShininessLocation(void) const;
		GLint getColorTextureLocation(void) const;
		void display(Window *w, GLuint buf) const;
	};
}

#endif
