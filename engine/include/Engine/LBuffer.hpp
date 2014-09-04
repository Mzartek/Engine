#ifndef LBUFFER
#define LBUFFER

#include "FrameBuffer.hpp"

namespace engine
{
	class DLLAPI LBuffer : public FrameBuffer
	{
	private:
		GLenum _colorAttachment;
		GLuint _idTexture;
	public:
		LBuffer(void);
		~LBuffer(void);
		void config(const GLuint &width, const GLuint &height);
		GLuint getIdTexture(void) const;
		void clear(void) const;
	};
}

#endif