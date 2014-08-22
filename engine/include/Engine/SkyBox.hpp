#ifndef SKYBOX
#define SKYBOX

#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "Camera.hpp"

namespace engine
{
	class DLLAPI SkyBox : public Object
	{
	private:
		GLuint _idTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		GLuint _idIBO;
		GLuint _numElement;
		glm::mat4 *_rotateMatrix;
		// Do not delete it
		ShaderProgram *_program;
		// Location or Index
		GLint _MVPLocation;
		GLint _textureLocation;
	public:
		SkyBox(void);
		~SkyBox(void);
		void load(const GLchar *posx, const GLchar *negx,
			const GLchar *posy, const GLchar *negy,
			const GLchar *posz, const GLchar *negz,
			GLfloat dim, ShaderProgram *program);
		void rotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void display(GBuffer *g, Camera *cam);
	};
}


#endif
