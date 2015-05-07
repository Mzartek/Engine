#ifndef FREECAM_HEADER
#define FREECAM_HEADER

#include "MovableCamera.hpp"

namespace Engine
{
	class DLLAPI FreeCam : public MovableCamera
	{
	public:
		FreeCam(void);
		FreeCam(GLfloat atheta, GLfloat aphi);
		~FreeCam(void);
		void keyboardMove(GLboolean f, GLboolean b, GLboolean l, GLboolean r) const;
	};
}

#endif
