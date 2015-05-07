#ifndef PERSPCAMERA_HEADER
#define PERSPCAMERA_HEADER

#include "Camera.hpp"

namespace Engine
{
	class DLLAPI PerspCamera : public Camera
	{
	protected:
		std::shared_ptr<glm::vec3> _pcamera;
		std::shared_ptr<glm::vec3> _vforward;
		std::shared_ptr<glm::vec3> _vleft;
		std::shared_ptr<glm::vec3> _vup;

		GLfloat _near;
		GLfloat _far;
		GLfloat _fov;
		GLfloat _frusSphereDistance;
		GLfloat _frusSphereRadius;
		std::shared_ptr<glm::vec3> _frusSpherePosition;

	public:
		PerspCamera(void);
		~PerspCamera(void);

		void setCameraPosition(const std::shared_ptr<glm::vec3> &pos);
		void setTargetPosition(GLfloat atheta, GLfloat aphi) const;
		void setPerspective(GLfloat fov, GLuint width, GLuint height, GLfloat n, GLfloat f);

		const std::shared_ptr<glm::vec3> &getCameraPosition(void) const;
		const std::shared_ptr<glm::vec3> &getForwardVector(void) const;
		const std::shared_ptr<glm::vec3> &getLeftVector(void) const;
		const std::shared_ptr<glm::vec3> &getUpVector(void) const;

		GLfloat getNear(void) const;
		GLfloat getFar(void) const;
		GLfloat getFOV(void) const;
		GLfloat getFrusSphereDistance(void) const;
		GLfloat getFrusSphereRadius(void) const;
		const std::shared_ptr<glm::vec3> &getFrusSpherePosition(void) const;

		void position(void) const;
	};
}

#endif