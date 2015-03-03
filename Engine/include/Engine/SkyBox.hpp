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
		ShaderProgram *_program;
		GLuint _idVAO;
		GLuint _numElement;
	public:
		SkyBox(ShaderProgram *program);
		~SkyBox(void);
		void load(const GLchar *posx, const GLchar *negx,
			const GLchar *posy, const GLchar *negy,
			const GLchar *posz, const GLchar *negz) const;
		Texture *getTexture(void) const;
		void display(GBuffer *gbuf, Camera *cam) const;
	};
}


#endif
