#ifndef FRAMEBUFFER_HEADER
#define FRAMEBUFFER_HEADER

#include "../Object.hpp"

namespace Engine
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
		virtual void config(GLuint width, GLuint height);
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLuint getIdFBO(void) const;
		virtual void clear(void) const = 0;
	};
}

#endif
