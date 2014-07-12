#ifndef SCREEN
#define SCREEN

#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "LBuffer.hpp"

namespace engine
{
	class DLLAPI Screen
	{
	private:
		GLuint _idVAO;
		GLuint _idVBO;
		ShaderProgram *_program;
		GLint _colorLocation;
		GLint _materialTextureLocation;
		GLint _lightTextureLocation;
	public:
		Screen();
		~Screen();
		void config(ShaderProgram *program);
		void display(GBuffer *gbuf, LBuffer *lbuf, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	};
}

#endif
