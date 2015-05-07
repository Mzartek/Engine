#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "../Object.hpp"

namespace Engine
{
	class DLLAPI Camera : public Object
	{
	protected:
		std::shared_ptr<glm::mat4> _projectionMatrix;
		std::shared_ptr<glm::mat4> _viewMatrix;
		std::shared_ptr<glm::mat4> _VPMatrix;
		std::shared_ptr<glm::mat4> _IVPMatrix;
	public:
		Camera(void);
		~Camera(void);
		const std::shared_ptr<glm::mat4> &getProjectionMatrix(void) const;
		const std::shared_ptr<glm::mat4> &getViewMatrix(void) const;
		const std::shared_ptr<glm::mat4> &getVPMatrix(void) const;
		const std::shared_ptr<glm::mat4> &getIVPMatrix(void) const;
		virtual void position(void) const = 0;
	};
}

#endif
