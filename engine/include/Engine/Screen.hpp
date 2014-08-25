#ifndef SCREEN
#define SCREEN

#include "ShaderProgram.hpp"
#include "GBuffer.hpp"

namespace engine
{
	class DLLAPI Screen : public Object
	{
	private:
		GLuint _idVAO;
		GLuint _idVBO;
		// Do not delete it
		ShaderProgram *_program;
		// Location or Index
		GLint _colorLocation;
		GLint _materialTextureLocation;
	public:
		Screen();
		~Screen();
		void config(ShaderProgram *program);
		void display(Renderer *renderer, GBuffer *gbuf, const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a);
	};
}

#endif
