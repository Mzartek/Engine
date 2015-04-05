#ifndef PERSPCAMERA_HEADER
#define PERSPCAMERA_HEADER

#include <Engine/Camera.hpp>

namespace Engine
{
	class DLLAPI PerspCamera : public Camera
	{
	protected:
		glm::vec3 *_pcamera;
		glm::vec3 *_ptarget;
		glm::vec3 *_vview;
		GLfloat _near;
		GLfloat _far;
		GLfloat _fov;
		GLfloat _frusSphereDistance;
		GLfloat _frusSphereRadius;
		glm::vec3 *_frusSpherePosition;
	public:
		PerspCamera(void);
		~PerspCamera(void);
		void setCameraPosition(const glm::vec3 &pos) const;
		void setTargetPosition(const glm::vec3 &pos) const;
		void setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f);
		glm::vec3 getCameraPosition(void) const;
		glm::vec3 getTargetPosition(void) const;
		glm::vec3 getViewVector(void) const;
		GLfloat getNear(void) const;
		GLfloat getFar(void) const;
		GLfloat getFOV(void) const;
		GLfloat getFrusSphereDistance(void) const;
		GLfloat getFrusSphereRadius(void) const;
		glm::vec3 getFrusSpherePosition(void) const;
		void position(void) const;
	};
}

#endif