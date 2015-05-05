#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

#include "Buffer.hpp"
#include "DepthMap.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "PerspCamera.hpp"

namespace Engine
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

		Buffer *_vertexBuffer;
		Buffer *_mainInfoBuffer;
		Buffer *_lightInfoBuffer;
		ShaderProgram *_program;
		GLuint _idVAO;
		glm::mat4 *_projectionMatrix;
		glm::mat4 *_viewMatrix;
		glm::mat4 *_VPMatrix;
	public:
		Light(ShaderProgram *program);
		~Light(void);
		virtual void display(const GBuffer &gbuf, const PerspCamera &cam) = 0;
	};
}

#endif
