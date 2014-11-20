#ifndef PARTICLESMANAGER_HEADER
#define PARTICLESMANAGER_HEADER

#include "Object.hpp"

namespace Engine
{
	class ShaderProgram;
	class Texture;
	class Buffer;
	class GBuffer;
	class Camera;

	class DLLAPI ParticlesManager : public Object
	{
	protected:
		ShaderProgram *_program;
		GLuint _idVAO;
		glm::mat4 *_modelMatrix;
		Texture *_colorTexture;
		Buffer *_matrixBuffer;
		Buffer *_vertexBuffer;
		GLsizei _numElement;
	public:
		ParticlesManager(ShaderProgram *program);
		~ParticlesManager(void);
		void setTexture(const GLchar *path);
		void setParticles(const GLfloat *particles, const GLsizei &numParticles);
		void display(GBuffer *gbuf, Camera *cam) const;
	};
}

#endif