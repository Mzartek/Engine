#ifndef GBUFFER_HEADER
#define GBUFFER_HEADER

#include "GraphicsRenderer.hpp"
#include "FrameBuffer.hpp"
#include "Buffer.hpp"
#include "ShaderProgram.hpp"

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
			std::shared_ptr<ShaderProgram> _backgroundProgram;

		public:
			GBuffer(const std::shared_ptr<ShaderProgram> &backgroundProgram);
			~GBuffer(void);
			void config(GLuint width, GLuint height);
			GLuint getIdTexture(GLuint num) const;
			void setSkyboxState(void) const;
			void setGeometryState(void) const;
			void setLightState(void) const;
			void setParticlesState(void) const;
			void background(void) const;
			void clear(void) const;
		};
	}
}

#endif
