#ifndef DIR_LIGHT
#define DIR_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI DirLight : public Light
	{
	public:
		DirLight(void);
		~DirLight(void);
		void config(ShaderProgram *program);
		void setMatrixDimension(const GLfloat &dim);
		void position(void);
		void display(GBuffer *g, Camera *cam);
	};
}

#endif
