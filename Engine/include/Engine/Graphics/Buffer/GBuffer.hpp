#ifndef GBUFFER_HEADER
#define GBUFFER_HEADER

#include "../ShaderProgram.hpp"

#include "FrameBuffer.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI GBuffer : public FrameBuffer
		{
		public:
			enum
			{
				NORMAL_ID = 0,
				MATERIAL_ID,
				LIGHT_ID,
				BACKGROUND_ID,
				DEPTHSTENCIL_ID,
				NUM_TEX
			};

		private:
			GLuint _idTexture[NUM_TEX];

		public:
			GBuffer(void);
			~GBuffer(void);
			void config(GLuint width, GLuint height) override;
			GLuint getIdTexture(GLuint num) const;
			void setSkyboxState(void) const;
			void setGeometryState(void) const;
			void setLightState(void) const;
			void setParticlesState(void) const;
			void setBackgroundState(void) const;
			void clear(void) const override;
			void clearLight(void) const;
		};
	}
}

#endif
