#ifndef ORTHOCAMERA_HEADER
#define ORTHOCAMERA_HEADER

#include "Camera.hpp"

namespace Engine
{
	class DLLAPI OrthoCamera : public Camera
	{
	protected:
		std::shared_ptr<glm::vec3> _position;
		std::shared_ptr<glm::vec3> _direction;
		GLfloat _left;
		GLfloat _right;
		GLfloat _bottom;
		GLfloat _top;
		GLfloat _zNear;
		GLfloat _zFar;
	public:
		OrthoCamera(void);
		~OrthoCamera(void);
		void setPosition(const std::shared_ptr<glm::vec3> &pos);
		void setDirection(const std::shared_ptr<glm::vec3> &dir);
		void setOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
		void position(void) const;
	};
}

#endif