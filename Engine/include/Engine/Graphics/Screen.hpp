#ifndef SCREEN_HEADER
#define SCREEN_HEADER

#include "../Object.hpp"

#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "Window.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI Screen : public Object
		{
		private:
			std::shared_ptr<Buffer> _vertexBuffer;
			std::shared_ptr<Buffer> _colorBuffer;
			std::shared_ptr<ShaderProgram> _backgroundProgram;
			std::shared_ptr<ShaderProgram> _directProgram;
			GLuint _idVAO;

		public:
			Screen(const std::shared_ptr<ShaderProgram> &backgroundProgram, const std::shared_ptr<ShaderProgram> &directProgram);
			~Screen(void);

			void genGBufferBackground(const std::shared_ptr<GBuffer> &gbuf) const;
			void display(const std::shared_ptr<Window> &window, const std::shared_ptr<GBuffer> &gbuf, const glm::vec4 &color) const;
		};
	}
}

#endif
