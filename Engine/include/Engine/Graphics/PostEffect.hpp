#ifndef POSTEFFECT_HEADER
#define POSTEFFECT_HEADER

#include "../Object.hpp"
#include "GraphicsRenderer.hpp"
#include "ShaderProgram.hpp"
#include "CBuffer.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI PostEffect : public Object
		{
		private:
			std::shared_ptr<ShaderProgram> _effectProgram;

		public:
			PostEffect(const std::shared_ptr<ShaderProgram> &effectProgram);
			~PostEffect(void);

			void display(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture);
		};
	}
}

#endif