#ifndef LBUFFER
#define LBUFFER

#include "FrameBuffer.hpp"

namespace engine
{
	class DLLAPI LBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[2];
	public:
		LBuffer(void);
		~LBuffer(void);
		void config(const GLuint &width, const GLuint &height);
		GLuint getIdTexture(GLuint num) const;
	};
}

#endif
