#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "Object.hpp"

namespace engine
{
	class DLLAPI ShaderProgram : public Object
	{
	private:
		GLuint _idProgram;
		GLuint _idVertexShader;
		GLuint _idFragmentShader;
		GLchar *readText(const GLchar *filename);
		GLuint loadShader(const GLchar *filename, const GLenum &type);
	public:
		ShaderProgram(void);
		~ShaderProgram(void);
		GLint loadProgram(const GLchar *vs, const GLchar *fs);
		GLuint getId(void);
	};
}

#endif
