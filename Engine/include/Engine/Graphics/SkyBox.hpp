#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

#define SKYBOX_DIM 10

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

#include "TextureCube.hpp"
#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "PerspCamera.hpp"

namespace Engine
{
	class DLLAPI SkyBox : public Object
	{
	private:
		TextureCube *_cubeTexture;
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
		TextureCube *getTexture(void) const;
		void display(GBuffer *gbuf, PerspCamera *cam) const;
	};
}


#endif
