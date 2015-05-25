#ifndef DEPTHMAP_HEADER
#define DEPTHMAP_HEADER

#include "FrameBuffer.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI DepthMap : public FrameBuffer
		{
		private:
			GLuint _idDepthTexture;

		public:
			DepthMap(void);
			~DepthMap(void);
			void config(GLuint width, GLuint height);
			GLuint getIdDepthTexture(void) const;
			void setState(void) const;
			void clear(void) const;
		};
	}
}

#endif
