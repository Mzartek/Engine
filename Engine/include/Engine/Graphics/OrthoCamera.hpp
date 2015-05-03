#ifndef ORTHOCAMERA_HEADER
#define ORTHOCAMERA_HEADER

#include "Camera.hpp"

namespace Engine
{
	class DLLAPI OrthoCamera : public Camera
	{
	protected:
		glm::vec3 *_position;
		glm::vec3 *_direction;
		GLfloat _left;
		GLfloat _right;
		GLfloat _bottom;
		GLfloat _top;
		GLfloat _zNear;
		GLfloat _zFar;
	public:
		OrthoCamera(void);
		~OrthoCamera(void);
		void setPosition(const glm::vec3 &pos) const;
		void setDirection(const glm::vec3 &dir) const;
		void setOrthogonal(const GLfloat &left, const GLfloat &right, const GLfloat &bottom, const GLfloat &top, const GLfloat &zNear, const GLfloat &zFar);
		void position(void) const;
	};
}

#endif