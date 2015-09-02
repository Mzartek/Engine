#ifndef MOVABLECAMERA_HEADER
#define MOVABLECAMERA_HEADER

#include "PerspCamera.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI MovableCamera : public PerspCamera
		{
		protected:
			GLfloat _speed;
			GLfloat _atheta;
			GLfloat _aphi;

		public:
			MovableCamera(void);
			MovableCamera(GLfloat atheta, GLfloat aphi);
			~MovableCamera(void);
			void setSpeed(GLfloat v);
			void mouseMove(GLint xrel, GLint yrel);
			virtual void keyboardMove(GLboolean f, GLboolean b, GLboolean l, GLboolean r) = 0;
		};
	}
}

#endif
