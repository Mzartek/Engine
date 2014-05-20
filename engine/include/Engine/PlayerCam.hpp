#ifndef PLAYER_CAM
#define PLAYER_CAM

#include "MovableCamera.hpp"

namespace engine
{
	class DLLAPI PlayerCam : public MovableCamera
	{
	public:
		PlayerCam(void);
		~PlayerCam(void);
		void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r);
	};
}

#endif
