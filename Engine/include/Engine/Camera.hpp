#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "Object.hpp"

namespace Engine
{
	class DLLAPI Camera : public Object
	{
	protected:
		glm::vec3 *_pcamera;
		glm::vec3 *_ptarget;
		glm::vec3 *_vview;
		glm::mat4 *_projectionMatrix;
		glm::mat4 *_viewMatrix;
		glm::mat4 *_VPMatrix;
		glm::mat4 *_IVPMatrix;
		GLfloat _fov;
		GLfloat _viewLen;
		GLfloat _frusSphereRadius;
	public:
		Camera(void);
		~Camera(void);
		void setCameraPosition(const glm::vec3 &pos);
		void setTargetPosition(const glm::vec3 &pos);
		void setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f);
		glm::vec3 getCameraPosition(void) const;
		glm::vec3 getTargetPosition(void) const;
		glm::vec3 getViewVector(void) const;
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getViewMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		glm::mat4 getIVPMatrix(void) const;
		GLfloat getFOV(void) const;
		GLfloat getFrusSphereRadius(void) const;
		void position(void);
	};
}

#endif
