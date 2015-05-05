#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

namespace Engine
{
	class DLLAPI Camera : public Object
	{
	protected:
		glm::mat4 *_projectionMatrix;
		glm::mat4 *_viewMatrix;
		glm::mat4 *_VPMatrix;
		glm::mat4 *_IVPMatrix;
	public:
		Camera(void);
		~Camera(void);
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getViewMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		glm::mat4 getIVPMatrix(void) const;
		virtual void position(void) const = 0;
	};
}

#endif