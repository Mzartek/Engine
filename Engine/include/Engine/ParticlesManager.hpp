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
	class Renderer;

	struct Particle
	{
        glm::vec3 pos;
		glm::vec3 dir;
        GLfloat life;
	};

	class DLLAPI ParticlesManager : public Object
	{
	protected:
		ShaderProgram *_physicsProgram;
		ShaderProgram *_displayProgram;
		GLuint _idTFO;
		GLuint _idVAO;
		glm::mat4 *_modelMatrix;
		Texture *_colorTexture;
		Buffer *_matrixBuffer;
		Buffer *_cameraBuffer;
		Buffer *_vertexBuffer[2];
		GLsizei _numElement;
	public:
		ParticlesManager(ShaderProgram *physicsProgram, ShaderProgram *displayProgram);
		~ParticlesManager(void);
		void setPosition(const glm::vec3 &pos);
		void setTexture(const GLchar *path);
		void setParticles(const Particle *particles, const GLsizei &numParticles);
		void updateParticles(void);
		void display(GBuffer *gbuf, Camera *cam) const;
	};
}

#endif
