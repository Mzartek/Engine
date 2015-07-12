#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "Buffer.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI Camera : public Object
		{
		protected:
			glm::mat4 _projectionMatrix;
			glm::mat4 _viewMatrix;
			glm::mat4 _VPMatrix;
			glm::mat4 _IVPMatrix;

			std::shared_ptr<Buffer> _cameraInfoBuffer;

		public:
			Camera(void);
			~Camera(void);

			const glm::mat4 &getProjectionMatrix(void) const;
			const glm::mat4 &getViewMatrix(void) const;
			const glm::mat4 &getVPMatrix(void) const;
			const glm::mat4 &getIVPMatrix(void) const;

			const std::shared_ptr<Buffer> &getCameraInfoBuffer(void) const;

			virtual void updateData(void) = 0;
		};
	}
}

#endif
