#ifndef GBUFFER
#define GBUFFER

#include "FrameBuffer.hpp"
#include "Renderer.hpp"

#define GBUF_NUM_TEX 5
#define GBUF_NORMAL 0
#define GBUF_MATERIAL 1
#define GBUF_LIGHT 2
#define GBUF_BACKGROUND 3
#define GBUF_DEPTH_STENCIL 4

namespace engine
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
		void setSkyboxConfig(void);
		void setGeometryConfig(void);
		void setLightConfig(void);
		void setBackgroundConfig(void);
		void clear(void) const;
		void clearLight(void) const;
	};
}

#endif
