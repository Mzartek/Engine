#ifndef LBUFFER
#define LBUFFER

#include "Window.hpp"
#include "FrameBuffer.hpp"

namespace engine
{
	class DLLAPI LBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture;
	public:
		LBuffer(void);
		~LBuffer(void);
		void config(const GLuint &width, const GLuint &height);
		GLuint getIdTexture(void) const;
	};
}

#endif
