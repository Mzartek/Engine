#ifndef FREECAM_HEADER
#define FREECAM_HEADER

#include "MovableCamera.hpp"

namespace Engine
{
	class DLLAPI FreeCam : public MovableCamera
	{
	public:
		FreeCam(void);
		FreeCam(const GLfloat &atheta, const GLfloat &aphi);
		~FreeCam(void);
		void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r) const;
	};
}

#endif
