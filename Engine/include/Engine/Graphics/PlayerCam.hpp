#ifndef PLAYERCAM_HEADER
#define PLAYERCAM_HEADER

#include "MovableCamera.hpp"

namespace Engine
{
	class DLLAPI PlayerCam : public MovableCamera
	{
	public:
		PlayerCam(void);
		PlayerCam(GLfloat atheta, GLfloat aphi);
		~PlayerCam(void);
		void keyboardMove(GLboolean f, GLboolean b, GLboolean l, GLboolean r) const;
	};
}

#endif
