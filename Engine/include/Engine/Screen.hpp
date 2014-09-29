#ifndef SCREEN
#define SCREEN

#include "Object.hpp"

namespace Engine
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
		Buffer *_colorBuffer;
		ShaderProgram *_backgroundProgram;
		ShaderProgram *_directProgram;
	public:
		Screen(void);
		~Screen(void);
		void config(ShaderProgram *backgroundProgram, ShaderProgram *directProgram);
		void background(GBuffer *gbuf);
		void display(Renderer *renderer, GBuffer *gbuf, const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a);
	};
}

#endif
