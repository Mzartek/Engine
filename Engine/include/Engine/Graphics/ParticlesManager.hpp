#ifndef PARTICLESMANAGER_HEADER
#define PARTICLESMANAGER_HEADER

#include "../Object.hpp"

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

		std::shared_ptr<ShaderProgram> _physicsProgram;
		std::shared_ptr<ShaderProgram> _displayProgram;
		GLuint _idTFO;
		GLuint _idVAO;
		std::shared_ptr<Texture2D> _colorTexture;
		std::shared_ptr<Buffer> _positionBuffer;
		std::shared_ptr<Buffer> _depthBuffer;
		std::shared_ptr<Buffer> _matrixBuffer;
		std::shared_ptr<Buffer> _vertexBuffer[2];
		GLsizei _numElement;
	public:
		ParticlesManager(const std::shared_ptr<ShaderProgram> &physicsProgram, const std::shared_ptr<ShaderProgram> &displayProgram);
		~ParticlesManager(void);
		void loadTexture(const GLchar *path) const;
		void setParticles(const Particle *particles, GLsizei numParticles);
		void setPosition(const std::shared_ptr<glm::vec3> &pos);
		const std::shared_ptr<glm::vec3> &getPosition(void) const;
		void updateParticles(void);
		void updateParticles(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam);
		void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<Camera> &cam);
	};
}

#endif
