#ifndef MOVABLECAMERA_HEADER
#define MOVABLECAMERA_HEADER

#include "PerspCamera.hpp"

namespace Engine
{
	class DLLAPI MovableCamera : public PerspCamera
	{
	protected:
		GLfloat _speed;
		GLfloat _atheta;
		GLfloat _aphi;
	public:
		MovableCamera(void);
		MovableCamera(const GLfloat &atheta, const GLfloat &aphi);
		~MovableCamera(void);
		void setSpeed(const GLfloat &v);
		void mouseMove(const GLint &xrel, const GLint &yrel);
		virtual void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r) const = 0;
	};
}

#endif
