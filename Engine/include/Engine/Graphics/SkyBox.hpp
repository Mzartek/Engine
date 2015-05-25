#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

#define SKYBOX_DIM 10

#include "../Object.hpp"

#include "TextureCube.hpp"
#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "PerspCamera.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI SkyBox : public Object
		{
		private:
			std::shared_ptr<TextureCube> _cubeTexture;
			std::shared_ptr<Buffer> _vertexBuffer;
			std::shared_ptr<Buffer> _indexBuffer;
			std::shared_ptr<Buffer> _MVPMatrixBuffer;
			std::shared_ptr<ShaderProgram> _program;
			GLuint _idVAO;
			GLuint _numElement;

		public:
			SkyBox(const std::shared_ptr<ShaderProgram> &program);
			~SkyBox(void);
			void load(const GLchar *posx, const GLchar *negx,
				const GLchar *posy, const GLchar *negy,
				const GLchar *posz, const GLchar *negz) const;
			const std::shared_ptr<TextureCube> &getTexture(void) const;
			void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) const;
		};
	}
}


#endif
