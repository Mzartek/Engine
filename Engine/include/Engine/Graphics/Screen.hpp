#ifndef SCREEN_HEADER
#define SCREEN_HEADER

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "Renderer.hpp"

namespace Engine
{
	class DLLAPI Screen : public Object
	{
	private:
		Buffer *_vertexBuffer;
		Buffer *_colorBuffer;
		ShaderProgram *_backgroundProgram;
		ShaderProgram *_directProgram;
		GLuint _idVAO;
	public:
		Screen(ShaderProgram *backgroundProgram, ShaderProgram *directProgram);
		~Screen(void);
		void background(const GBuffer &gbuf) const;
		void display(const Renderer &renderer, const GBuffer &gbuf, const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a) const;
	};
}

#endif
