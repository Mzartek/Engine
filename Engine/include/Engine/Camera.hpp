#ifndef CAMERA
#define CAMERA

#include "Object.hpp"

namespace engine
{
	class DLLAPI Camera : public Object
	{
	protected:
		glm::vec3 *_pcamera;
		glm::vec3 *_ptarget;
		glm::mat4 *_projectionMatrix;
		glm::mat4 *_VPMatrix;
	public:
		Camera(void);
		~Camera(void);
		void setPositionCamera(const glm::vec3 &pos);
		void setPositionTarget(const glm::vec3 &pos);
		void setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f);
		glm::vec3 getPositionCamera(void) const;
		glm::vec3 getPositionTarget(void) const;
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		void position(void);
	};
}

#endif