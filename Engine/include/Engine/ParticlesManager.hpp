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
			glm::mat4 MVP;
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 modelMatrix;
		} _matrix;

		struct
		{
			glm::vec3 ALIGN(16) position;
			glm::vec3 ALIGN(16) target;
		} _camera;

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
		void setTexture(const GLchar *path) const;
		void setParticles(const Particle *particles, const GLsizei &numParticles);
		void matIdentity(void) const;
		void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
		void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
		void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
		glm::vec3 getPosition(void) const;
		void updateParticles(void);
		void display(GBuffer *gbuf, Camera *cam);
	};
}

#endif
