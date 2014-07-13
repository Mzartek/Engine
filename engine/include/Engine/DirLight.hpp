#ifndef DIR_LIGHT
#define DIR_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI DirLight : public Light
	{
	private:
		GLfloat _projection[16];
		GLint _lightDirectionLocation;
	public:
		DirLight(void);
		~DirLight(void);
		void config(ShaderProgram *program);
		void setDimension(GLfloat x, GLfloat y, GLfloat z);
		void position(void);
		void display(GBuffer *g, Camera *cam);
	};
}

#endif
