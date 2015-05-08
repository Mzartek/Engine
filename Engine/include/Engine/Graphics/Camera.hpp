#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "../Object.hpp"

namespace Engine
{
	class DLLAPI Camera : public Object
	{
	protected:
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
		glm::mat4 _VPMatrix;
		glm::mat4 _IVPMatrix;

	public:
		Camera(void);
		~Camera(void);
		const glm::mat4 &getProjectionMatrix(void) const;
		const glm::mat4 &getViewMatrix(void) const;
		const glm::mat4 &getVPMatrix(void) const;
		const glm::mat4 &getIVPMatrix(void) const;
		virtual void position(void) = 0;
	};
}

#endif
