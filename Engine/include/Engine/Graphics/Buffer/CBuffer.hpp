#ifndef CBUFFER_HEADER
#define CBUFFER_HEADER

#include "FrameBuffer.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI CBuffer : public FrameBuffer
		{
			GLuint _idTexture;

		public:
			CBuffer(void);
			~CBuffer(void);
			void config(GLuint width, GLuint height) override;
			GLuint getIdTexture(void) const;
			void setNormalState(void) const;
			void setAdditiveState(void) const;
			void setTransparentState(void) const;
			void clear(void) const override;
		};
	}
}

#endif