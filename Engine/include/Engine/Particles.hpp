#ifndef PARTICLES_HEADER
#define PARTICLES_HEADER

#include "Object.hpp"

namespace Engine
{
	class ShaderProgram;
	class Buffer;

	class DLLAPI Particles : public Object
	{
	protected:
		ShaderProgram *_program;
		GLuint _idVAO;
		Buffer *_vertexBuffer;
		GLsizei _numElement;
	public:
		Particles(ShaderProgram *program);
		~Particles(void);
	};
}

#endif