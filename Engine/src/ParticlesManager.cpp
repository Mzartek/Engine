#include <Engine/ParticlesManager.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>

Engine::ParticlesManager::ParticlesManager(ShaderProgram *program)
	: _program(program), _numElement(0)
{
	_modelMatrix = new glm::mat4;
	_colorTexture = new Texture;
	_matrixBuffer = new Buffer;
	_vertexBuffer = new Buffer;

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 4 * sizeof(glm::mat4), GL_DYNAMIC_DRAW);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "colorTexture"), 0);

	glGenVertexArrays(1, &_idVAO);
}

Engine::ParticlesManager::~ParticlesManager(void)
{
	delete _modelMatrix;
	delete _colorTexture;
	delete _matrixBuffer;
	delete _vertexBuffer;

	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::ParticlesManager::setTexture(const GLchar *path)
{
	_colorTexture->load2DTextureFromFile(path);
}

void Engine::ParticlesManager::setParticles(const GLfloat *particles, const GLsizei &numParticles)
{
	_numElement = numParticles;

	_vertexBuffer->createStore(GL_ARRAY_BUFFER, particles, numParticles * 3 * sizeof(GLfloat), GL_STATIC_DRAW);

	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
}

void Engine::ParticlesManager::display(GBuffer *gbuf, Camera *cam) const
{
	gbuf->setBackgroundState();

	glUseProgram(_program->getId());

	struct
	{
		glm::mat4 MVP;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 modelMatrix;
	} matrix;
	matrix.MVP = cam->getVPMatrix() * *_modelMatrix;
	matrix.projectionMatrix = cam->getProjectionMatrix();
	matrix.viewMatrix = cam->getViewMatrix();
	matrix.modelMatrix = *_modelMatrix;
	_matrixBuffer->updateStoreMap(&matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_POINTS, 0, _numElement);
}