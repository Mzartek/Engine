#ifndef DIR_LIGHT
#define DIR_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI DirLight : public Light
	{
	private:
		GLfloat _dim[3];
		GLint _lightDirectionLocation;
	public:
		DirLight(void);
		~DirLight(void);
		void config(ShaderProgram *program);
		void setDimension(GLfloat x, GLfloat y, GLfloat z);
		GLint getLightDirectionLocation(void) const;
		void position(void);
		void display(Camera *cam, GBuffer *g, LBuffer *l);
	};
}

#endif
