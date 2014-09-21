#ifndef SCREEN
#define SCREEN

#include "Object.hpp"

namespace engine
{
	class Buffer;
	class ShaderProgram;
	class GBuffer;
	class Renderer;

	class DLLAPI Screen : public Object
	{
	private:
		GLuint _idVAO;
		Buffer *_vertexBuffer;
		// Location or Index
		ShaderProgram *_backgroundProgram;
		ShaderProgram *_directProgram;
		GLint _bMaterialTextureLocation;
		GLint _bLightTextureLocation;
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
