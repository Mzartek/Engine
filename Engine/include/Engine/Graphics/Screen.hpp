#ifndef SCREEN_HEADER
#define SCREEN_HEADER

#include "Engine/Graphics/GraphicsRenderer.hpp"
#include "Engine/Graphics/ShaderProgram.hpp"
#include "Engine/Graphics/Buffer.hpp"
#include "Engine/Graphics/GBuffer.hpp"
#include "Engine/Graphics/CBuffer.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI Screen : public Object
		{
		private:
			std::shared_ptr<Buffer> _vertexBuffer;
			std::shared_ptr<Buffer> _colorBuffer;
			GLuint _idVAO;

		public:
			static Screen &Instance(void);

		private:
			Screen(void);
			~Screen(void);

		public:
			GLuint getVertexArray(void);

			void displayOnScreen(const std::shared_ptr<GBuffer> &gbuffer, const glm::vec4 &color, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
			void displayOnScreen(const std::shared_ptr<CBuffer> &cbuffer, const glm::vec4 &color, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
			
			void displayOnCBuffer(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<CBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
			void displayOnCBuffer(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<GBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
			void displayOnCBufferAdditive(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<CBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
			void displayOnCBufferAdditive(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<GBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
			void displayOnCBufferTransparent(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<CBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
			void displayOnCBufferTransparent(const std::shared_ptr<CBuffer> &cbuffer, const std::shared_ptr<GBuffer> &input, const std::shared_ptr<ShaderProgram> &shaderProgram) const;

			void displayGBufferBackground(const std::shared_ptr<GBuffer> &gbuffer, const std::shared_ptr<ShaderProgram> &shaderProgram) const;
		};
	}
}

#endif