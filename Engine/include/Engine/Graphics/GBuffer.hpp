#ifndef GBUFFER_HEADER
#define GBUFFER_HEADER

#include "FrameBuffer.hpp"

#define GBUF_NUM_TEX 5
#define GBUF_NORMAL 0
#define GBUF_MATERIAL 1
#define GBUF_LIGHT 2
#define GBUF_BACKGROUND 3
#define GBUF_DEPTH_STENCIL 4

namespace Engine
{
	class DLLAPI GBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[GBUF_NUM_TEX];
	public:
		GBuffer(void);
		~GBuffer(void);
		void config(const GLuint &width, const GLuint &height);
		GLuint getIdTexture(const GLuint &num) const;
		void setSkyboxState(void) const;
		void setGeometryState(void) const;
		void setLightState(void) const;
		void setParticlesState(void) const;
		void setBackgroundState(void) const;
		void clear(void) const;
		void clearLight(void) const;
	};
}

#endif
