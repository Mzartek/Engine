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
		GLint getLightDirectionLocation(void) const;
		void position(void);
		void display(LBuffer *l, GBuffer *g, Camera *cam);
	};
}

#endif
