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
		class DLLAPI PostProcessing : public Object
		{
		private:
			std::shared_ptr<ShaderProgram> _effectProgram;

		public:
			PostProcessing(const std::shared_ptr<ShaderProgram> &effectProgram);
			~PostProcessing(void);

			void display(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture);
			void displayAdditive(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture);
			void displayTransparent(const std::shared_ptr<CBuffer> &cbuf, GLuint idTexture);
		};
	}
}

#endif