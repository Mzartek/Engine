#ifndef FREE_CAM
#define FREE_CAM

#include "MovableCamera.hpp"

namespace engine
{
	class DLLAPI FreeCam : public MovableCamera
	{
	public:
		FreeCam(void);
		FreeCam(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		~FreeCam(void);
		void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r);
	};
}

#endif
