#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "../../Object.hpp"

#include "../Buffer/Buffer.hpp"
#include "../Buffer/GBuffer.hpp"
#include "../Buffer/DepthMap.hpp"

#include "../Camera/PerspCamera.hpp"

#include "../Screen.hpp"
#include "../ShaderProgram.hpp"

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
				glm::vec3 ALIGN(16) camPosition;
				GLint withShadowMapping;
			} _mainInfo;

			std::shared_ptr<Buffer> _mainInfoBuffer;
			std::shared_ptr<Buffer> _lightInfoBuffer;
			std::shared_ptr<ShaderProgram> _program;

		public:
			Light(const std::shared_ptr<ShaderProgram> &program);
			~Light(void);
			virtual void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) = 0;
		};
	}
}

#endif
