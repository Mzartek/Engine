#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

#define SKYBOX_DIM 10

#include "Object.hpp"

namespace Engine
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
		Buffer *_vertexBuffer;
		Buffer *_indexBuffer;
		Buffer *_MVPMatrixBuffer;
		glm::mat4 *_rotateMatrix;
		ShaderProgram *_program;
		GLuint _idVAO;
		GLuint _numElement;
	public:
		SkyBox(ShaderProgram *program);
		~SkyBox(void);
		void load(const GLchar *posx, const GLchar *negx,
			const GLchar *posy, const GLchar *negy,
			const GLchar *posz, const GLchar *negz);
		void rotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void display(GBuffer *gbuf, Camera *cam) const;
	};
}


#endif
