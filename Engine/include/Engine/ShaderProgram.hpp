#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "Object.hpp"

namespace Engine
{
	class DLLAPI ShaderProgram : public Object
	{
	private:
		GLuint _idProgram;
		GLuint _idVertexShader;
		GLuint _idTessControlShader;
		GLuint _idTessEvaluationShader;
		GLuint _idGeometryShader;
		GLuint _idFragmentShader;
	public:
		ShaderProgram(void);
		~ShaderProgram(void);
		void loadProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs);
		GLuint getId(void);
	};
}

#endif
