#ifndef SKYBOX
#define SKYBOX

#include "Object.hpp"

namespace engine
{
	class Texture;
	class Buffer;
	class ShaderProgram;
	class GBuffer;
	class Camera;

	class DLLAPI SkyBox : public Object
	{
	private:
		Texture *_cubeTexture;
		GLuint _idVAO;
		Buffer *_vertexBuffer;
		Buffer *_indexBuffer;
		glm::mat4 *_rotateMatrix;
		// Do not delete it
		ShaderProgram *_program;
		GLint _MVPLovation;
		GLint _cubeMapLocation;
		GLuint _numElement;
	public:
		SkyBox(void);
		~SkyBox(void);
		void load(const GLchar *posx, const GLchar *negx,
			const GLchar *posy, const GLchar *negy,
			const GLchar *posz, const GLchar *negz,
			GLfloat dim, ShaderProgram *program);
		void rotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void display(GBuffer *gbuf, Camera *cam) const;
	};
}


#endif
