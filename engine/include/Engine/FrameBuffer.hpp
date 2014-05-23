#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include "GLHead.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
	class DLLAPI FrameBuffer
	{
	protected:
		GLuint _width;
		GLuint _height;
		GLuint _idFBO;
		GLuint _idTexture;
		ShaderProgram *_program;
	public:
		FrameBuffer(void);
		virtual ~FrameBuffer(void);
		virtual void config(const GLuint &width, const GLuint &height, ShaderProgram *program) = 0;
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLuint getIdFBO(void) const;
		GLuint getIdTexture(void) const;
		GLuint getProgramId(void) const;
		void clear(void) const;
	};
}

#endif
