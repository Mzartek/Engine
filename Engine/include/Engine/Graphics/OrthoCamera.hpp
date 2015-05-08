#ifndef ORTHOCAMERA_HEADER
#define ORTHOCAMERA_HEADER

#include "Camera.hpp"

namespace Engine
{
	class DLLAPI OrthoCamera : public Camera
	{
	protected:
		glm::vec3 _position;
		glm::vec3 _direction;
		GLfloat _left;
		GLfloat _right;
		GLfloat _bottom;
		GLfloat _top;
		GLfloat _zNear;
		GLfloat _zFar;

	public:
		OrthoCamera(void);
		~OrthoCamera(void);
		void setPosition(const glm::vec3 &pos);
		void setDirection(const glm::vec3 &dir);
		void setOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
		void position(void);
	};
}

#endif