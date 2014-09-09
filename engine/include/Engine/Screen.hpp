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
		// Location or Index
		ShaderProgram *_backgroundProgram;
		GLint _bMaterialTextureLocation;
		GLint _bLightTextureLocation;
		ShaderProgram *_directProgram;
		GLint _dBackgroundTextureLocation;
		GLint _dColorLocation;
	public:
		Screen();
		~Screen();
		void config(ShaderProgram *backgroundProgram, ShaderProgram *directProgram);
		void background(GBuffer *gbuf);
		void display(Renderer *renderer, GBuffer *gbuf, const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a);
	};
}

#endif
