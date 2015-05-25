#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "../Object.hpp"

#include "Buffer.hpp"
#include "DepthMap.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "PerspCamera.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI Light : public Object
		{
		protected:
			struct
			{
				glm::mat4 IVPMatrix;
				glm::uvec2 ALIGN(16) screen;
				glm::vec3 ALIGN(16) camPosition;
				GLint withShadowMapping;
			} _mainInfo;

			std::shared_ptr<Buffer> _vertexBuffer;
			std::shared_ptr<Buffer> _mainInfoBuffer;
			std::shared_ptr<Buffer> _lightInfoBuffer;
			std::shared_ptr<ShaderProgram> _program;
			GLuint _idVAO;

		public:
			Light(const std::shared_ptr<ShaderProgram> &program);
			~Light(void);
			virtual void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) = 0;
		};
	}
}

#endif
