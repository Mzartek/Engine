#ifndef MOVABLE_CAMERA
#define MOVABLE_CAMERA

#include "Camera.hpp"

namespace engine
{
	class DLLAPI MovableCamera : public Camera
	{
	private:
		GLfloat _atheta;
		GLfloat _aphi;
	protected:
		glm::vec3 *_vforward;
		glm::vec3 *_vleft;
		GLfloat _speed;
	public:
		MovableCamera(void);
		~MovableCamera(void);
		void setInitialAngle(const GLfloat &t, const GLfloat &p);
		void setSpeed(const GLfloat &v);
		void mouseMove(const GLint &xrel, const GLint &yrel);
		glm::vec3 getForward(void) const;
		glm::vec3 getLeft(void) const;
		virtual void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r) = 0;
	};
}

#endif
