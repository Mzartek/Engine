#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include "GLHead.hpp"

namespace engine
{
	class DLLAPI FrameBuffer
	{
	protected:
		GLuint _width;
		GLuint _height;
		GLuint _idFBO;
	public:
		FrameBuffer(void);
		virtual ~FrameBuffer(void);
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLuint getIdFBO(void) const;
		void clear(void) const;
	};
}

#endif
