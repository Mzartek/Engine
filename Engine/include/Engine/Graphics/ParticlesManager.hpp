#ifndef PARTICLESMANAGER_HEADER
#define PARTICLESMANAGER_HEADER

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

#include "ShaderProgram.hpp"
#include "Texture2D.hpp"
#include "Buffer.hpp"
#include "GBuffer.hpp"
#include "Camera.hpp"
#include "DepthMap.hpp"

namespace Engine
{
	struct Particle
	{
        glm::vec3 position;
		glm::vec3 direction;
		GLfloat velocity;
        GLfloat life;
	};

	class DLLAPI ParticlesManager : public Object
	{
	protected:
		struct
		{
			glm::vec3 ALIGN(16) position;
		} _position;

		struct
		{
			glm::mat4 ALIGN(16) depthMatrix;
		} _depth;

		struct
		{
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
		} _matrix;

		ShaderProgram *_physicsProgram;
		ShaderProgram *_displayProgram;
		GLuint _idTFO;
		GLuint _idVAO;
		Texture2D *_colorTexture;
		Buffer *_positionBuffer;
		Buffer *_depthBuffer;
		Buffer *_matrixBuffer;
		Buffer *_vertexBuffer[2];
		GLsizei _numElement;
	public:
		ParticlesManager(ShaderProgram *physicsProgram, ShaderProgram *displayProgram);
		~ParticlesManager(void);
		void loadTexture(const GLchar *path) const;
		void setParticles(const Particle *particles, const GLsizei &numParticles);
		void setPosition(const glm::vec3 &pos);
		glm::vec3 getPosition(void) const;
		void updateParticles(void);
		void updateParticles(DepthMap *dmap, Camera *cam);
		void display(GBuffer *gbuf, Camera *cam);
	};
}

#endif
