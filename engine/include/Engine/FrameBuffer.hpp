#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include "Object.hpp"

namespace engine
{
	class DLLAPI FrameBuffer : public Object
	{
	protected:
		GLuint _width;
		GLuint _height;
		GLuint _idFBO;
	public:
		FrameBuffer(void);
		~FrameBuffer(void);
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLuint getIdFBO(void) const;
		virtual void clear(void) const = 0;
	};
}

#endif
