#ifndef SHADOW_MAP
#define SHADOW_MAP

#include "GLHead.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
	class DLLAPI ShadowMap
	{
	private:
		GLuint _width;
		GLuint _height;
		GLuint _idFBO;
		GLuint _idDepthTexture;
		ShaderProgram *_program;
	public:
		GLint MVPLocation;
		ShadowMap(void);
		~ShadowMap(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLuint getIdFBO(void) const;
		GLuint getIdDepthTexture(void) const;
		GLuint getProgramId(void) const;
		void clear(void);
	};
}

#endif
