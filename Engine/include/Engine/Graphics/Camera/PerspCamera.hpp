#ifndef PERSPCAMERA_HEADER
#define PERSPCAMERA_HEADER

#include "Camera.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI PerspCamera : public Camera
		{
		protected:
			struct
			{
				glm::vec3 ALIGN(16) position;
				glm::vec3 ALIGN(16) forward;
				glm::vec3 ALIGN(16) left;
				glm::vec3 ALIGN(16) up;
			} _cameraInfo;

			GLfloat _near;
			GLfloat _far;
			GLfloat _fov;
			GLfloat _frusSphereDistance;
			GLfloat _frusSphereRadius;
			glm::vec3 _frusSpherePosition;

		public:
			PerspCamera(void);
			~PerspCamera(void);

			void setCameraPosition(const glm::vec3 &pos);
			void setAngle(GLfloat atheta, GLfloat aphi);
			void setPositionAndTarget(const glm::vec3 &pos, const glm::vec3 &tar);
			void setPerspective(GLfloat fov, GLuint width, GLuint height, GLfloat n, GLfloat f);

			const glm::vec3 &getCameraPosition(void) const;
			const glm::vec3 &getForwardVector(void) const;
			const glm::vec3 &getLeftVector(void) const;
			const glm::vec3 &getUpVector(void) const;

			GLfloat getNear(void) const;
			GLfloat getFar(void) const;
			GLfloat getFOV(void) const;
			GLfloat getFrusSphereDistance(void) const;
			GLfloat getFrusSphereRadius(void) const;
			const glm::vec3 &getFrusSpherePosition(void) const;

			void updateData(void) override;
		};
	}
}

#endif