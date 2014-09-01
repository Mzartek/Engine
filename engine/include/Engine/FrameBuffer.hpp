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
		virtual void config(const GLuint &width, const GLuint &height) = 0;
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLuint getIdFBO(void) const;
		virtual void clear(void) const = 0;
	};
}

#endif
