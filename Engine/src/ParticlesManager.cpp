#include <Engine/ParticlesManager.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Renderer.hpp>

Engine::ParticlesManager::ParticlesManager(ShaderProgram *physicsProgram, ShaderProgram *displayProgram)
	: _physicsProgram(physicsProgram), _displayProgram(displayProgram), _activeVertex(0), _numElement(0)
{
	_modelMatrix = new glm::mat4;
	_colorTexture = new Texture;
	_matrixBuffer = new Buffer;
	_vertexBuffer[0] = new Buffer;
	_vertexBuffer[1] = new Buffer;

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 4 * sizeof(glm::mat4), GL_DYNAMIC_DRAW);

	glUseProgram(displayProgram->getId());
	glUniform1i(glGetUniformLocation(displayProgram->getId(), "colorTexture"), 0);

	glGenTransformFeedbacks(1, &_idTFO);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _idTFO);

	glUseProgram(0);
	const GLchar *varyings[] =
	{
		"outPosition",
		"outDirection",
		"outLife",
	};
	glTransformFeedbackVaryings(_physicsProgram->getId(), 3, varyings, GL_INTERLEAVED_ATTRIBS);
}

Engine::ParticlesManager::~ParticlesManager(void)
{
	delete _modelMatrix;
	delete _colorTexture;
	delete _matrixBuffer;
	delete _vertexBuffer[0];
	delete _vertexBuffer[1];

	glDeleteTransformFeedbacks(1, &_idTFO);
}

void Engine::ParticlesManager::setPosition(const glm::vec3 &pos)
{
    *_modelMatrix = glm::translate(pos);
}

void Engine::ParticlesManager::setTexture(const GLchar *path)
{
	_colorTexture->load2DTextureFromFile(path);
}

void Engine::ParticlesManager::setParticles(const Particle *particles, const GLsizei &numParticles)
{
	_numElement = numParticles;

	_vertexBuffer[_activeVertex]->createStore(GL_ARRAY_BUFFER, particles, numParticles * sizeof *particles, GL_DYNAMIC_DRAW);
	_vertexBuffer[!_activeVertex]->createStore(GL_ARRAY_BUFFER, NULL, numParticles * sizeof *particles, GL_DYNAMIC_DRAW);
}

void Engine::ParticlesManager::updateParticles(void)
{
	glEnable(GL_RASTERIZER_DISCARD);

	glUseProgram(_physicsProgram->getId());
	
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _idTFO);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _vertexBuffer[!_activeVertex]->getId());
	glBeginTransformFeedback(GL_POINTS);
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer[_activeVertex]->getId());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
		glDrawArrays(GL_POINTS, 0, _numElement);
	}
	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

	_activeVertex = !_activeVertex;
}

void Engine::ParticlesManager::display(GBuffer *gbuf, Camera *cam) const
{
	gbuf->setGeometryState();

	glUseProgram(_displayProgram->getId());

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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer[_activeVertex]->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
	glDrawArrays(GL_POINTS, 0, _numElement);
}
