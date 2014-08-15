#ifndef CAMERA
#define CAMERA

#include "ShaderProgram.hpp"

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
		Camera(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		~Camera(void);
		void setPositionCamera(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void setPositionTarget(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f);
		glm::vec3 getPositionCamera(void) const;
		glm::vec3 getPositionTarget(void) const;
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		void position(void);
	};
}

#endif
