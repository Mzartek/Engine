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
		GLint _MVPLocation;
		GLint _modelMatrixLocation;
		GLint _normalMatrixLocation;
		GLint _matAmbientLocation;
		GLint _matDiffuseLocation;
		GLint _matSpecularLocation;
		GLint _matShininessLocation;
		GLint _colorTextureLocation;
		GLint _gBufferMaterialTextureLocation;
	public:
		GBuffer(void);
		~GBuffer(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
		GLuint getIdTexture(GLuint num) const;
		GLuint getIdDepthRender(void) const;
		GLint getMVPLocation(void) const;
		GLint getModelMatrixLocation(void) const;
		GLint getNormalMatrixLocation(void) const;
		GLint getMatAmbientLocation(void) const;
		GLint getMatDiffuseLocation(void) const;
		GLint getMatSpecularLocation(void) const;
		GLint getMatShininessLocation(void) const;
		GLint getColorTextureLocation(void) const;
		GLint getGBufferMaterialTextureLocation(void) const;
		void display(Window *w, GLuint buf) const;
	};
}

#endif
