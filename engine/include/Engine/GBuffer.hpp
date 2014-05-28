#ifndef GBUFFER
#define GBUFFER

#include "FrameBuffer.hpp"
#include "Window.hpp"

namespace engine
{
	class DLLAPI GBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[4];
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
		void display(Window *w);
		GLuint getIdTexture(GLuint num) const;
		GLuint getIdDepthRender(void) const;
		GLint getMVPLocation(void) const;
		GLint getModelMatrixLocation(void) const;
		GLint getNormalMatrixLocation(void) const;
		GLint getShininessLocation(void) const;
		GLint getColorTextureLocation(void) const;
	};
}

#endif
