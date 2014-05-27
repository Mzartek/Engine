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
		ShaderProgram *_program;
	public:
		FrameBuffer(void);
		virtual ~FrameBuffer(void);
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLuint getIdFBO(void) const;
		GLuint getProgramId(void) const;
		void clear(void) const;
	};
}

#endif
