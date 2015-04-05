#include <Engine/ParticlesManager.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Texture2D.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/DepthMap.hpp>

Engine::ParticlesManager::ParticlesManager(ShaderProgram *physicsProgram, ShaderProgram *displayProgram)
	: _physicsProgram(physicsProgram), _displayProgram(displayProgram), _numElement(0)
{
	_colorTexture = new Texture2D;
	_mainBuffer = new Buffer;
	_matrixBuffer = new Buffer;
	_vertexBuffer[0] = new Buffer;
	_vertexBuffer[1] = new Buffer;

	_mainBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _main, GL_DYNAMIC_DRAW);
	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);

	glUseProgram(physicsProgram->getId());
	glUniform1i(glGetUniformLocation(displayProgram->getId(), "depthMap"), 0);
	glUseProgram(displayProgram->getId());
	glUniform1i(glGetUniformLocation(displayProgram->getId(), "colorTexture"), 0);
	glUniform1i(glGetUniformLocation(displayProgram->getId(), "depthTexture"), 1);

	glGenTransformFeedbacks(1, &_idTFO);
	glGenVertexArrays(1, &_idVAO);
}

Engine::ParticlesManager::~ParticlesManager(void)
{
	delete _colorTexture;
	delete _mainBuffer;
	delete _matrixBuffer;
	delete _vertexBuffer[0];
	delete _vertexBuffer[1];

	glDeleteTransformFeedbacks(1, &_idTFO);
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::ParticlesManager::loadTexture(const GLchar *path) const
{
	_colorTexture->loadFromFile(path);
}

void Engine::ParticlesManager::setParticles(const Particle *particles, const GLsizei &numParticles)
{
	_numElement = numParticles;

	_vertexBuffer[0]->createStore(GL_ARRAY_BUFFER, particles, numParticles * sizeof *particles, GL_DYNAMIC_DRAW);
	_vertexBuffer[1]->createStore(GL_ARRAY_BUFFER, NULL, numParticles * sizeof *particles, GL_DYNAMIC_DRAW);
}

void Engine::ParticlesManager::setPosition(const glm::vec3 &pos)
{
	_main.position = pos;
}

glm::vec3 Engine::ParticlesManager::getPosition(void) const
{
	return _main.position;
}

void Engine::ParticlesManager::updateParticles(void)
{
	glEnable(GL_RASTERIZER_DISCARD);

	glUseProgram(_physicsProgram->getId());

	_mainBuffer->updateStoreMap(&_main);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainBuffer->getId());

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _idTFO);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _vertexBuffer[1]->getId());
	glBeginTransformFeedback(GL_POINTS);
	{
		glBindVertexArray(_idVAO);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer[0]->getId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(7 * sizeof(GLfloat)));
		glDrawArrays(GL_POINTS, 0, _numElement);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	glEndTransformFeedback();
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	glDisable(GL_RASTERIZER_DISCARD);

	std::swap(_vertexBuffer[0], _vertexBuffer[1]);
}

void Engine::ParticlesManager::updateParticles(DepthMap *dmap, Camera *cam)
{
	glEnable(GL_RASTERIZER_DISCARD);

	glUseProgram(_physicsProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dmap->getIdDepthTexture());

	_main.depthMatrix = cam->getVPMatrix();
	_mainBuffer->updateStoreMap(&_main);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mainBuffer->getId());

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _idTFO);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _vertexBuffer[1]->getId());
	glBeginTransformFeedback(GL_POINTS);
	{
		glBindVertexArray(_idVAO);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer[0]->getId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(7 * sizeof(GLfloat)));
		glDrawArrays(GL_POINTS, 0, _numElement);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	glEndTransformFeedback();
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	glDisable(GL_RASTERIZER_DISCARD);

	std::swap(_vertexBuffer[0], _vertexBuffer[1]);
}

void Engine::ParticlesManager::display(GBuffer *gbuf, Camera *cam)
{
	gbuf->setParticlesState();

	glUseProgram(_displayProgram->getId());

	_matrix.projectionMatrix = cam->getProjectionMatrix();
	_matrix.viewMatrix = cam->getViewMatrix();
	_matrixBuffer->updateStoreMap(&_matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_DEPTH_STENCIL));

	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer[0]->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(7 * sizeof(GLfloat)));
	glDrawArrays(GL_POINTS, 0, _numElement);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
