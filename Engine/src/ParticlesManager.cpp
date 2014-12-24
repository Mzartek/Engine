#include <Engine/ParticlesManager.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Renderer.hpp>

Engine::ParticlesManager::ParticlesManager(ShaderProgram *physicsProgram, ShaderProgram *displayProgram)
	: _physicsProgram(physicsProgram), _displayProgram(displayProgram), _numElement(0)
{
	_modelMatrix = new glm::mat4;
	_colorTexture = new Texture;
	_matrixBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_vertexBuffer[0] = new Buffer;
	_vertexBuffer[1] = new Buffer;

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 4 * sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	_cameraBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 2 * sizeof(glm::vec4), GL_DYNAMIC_DRAW);

	glUseProgram(displayProgram->getId());
	glUniform1i(glGetUniformLocation(displayProgram->getId(), "colorTexture"), 0);
	glUniform1i(glGetUniformLocation(displayProgram->getId(), "depthTexture"), 1);

	glGenTransformFeedbacks(1, &_idTFO);
	glGenVertexArrays(1, &_idVAO);
}

Engine::ParticlesManager::~ParticlesManager(void)
{
	delete _modelMatrix;
	delete _colorTexture;
	delete _matrixBuffer;
	delete _cameraBuffer;
	delete _vertexBuffer[0];
	delete _vertexBuffer[1];

	glDeleteTransformFeedbacks(1, &_idTFO);
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::ParticlesManager::setTexture(const GLchar *path)
{
	_colorTexture->load2DTextureFromFile(path);
}

void Engine::ParticlesManager::setParticles(const Particle *particles, const GLsizei &numParticles)
{
	_numElement = numParticles;

	_vertexBuffer[0]->createStore(GL_ARRAY_BUFFER, particles, numParticles * sizeof *particles, GL_DYNAMIC_DRAW);
	_vertexBuffer[1]->createStore(GL_ARRAY_BUFFER, NULL, numParticles * sizeof *particles, GL_DYNAMIC_DRAW);
}

void Engine::ParticlesManager::matIdentity(void)
{
	*_modelMatrix = glm::mat4(1.0f);
}

void Engine::ParticlesManager::matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::translate(glm::vec3(x, y, z));
}

void Engine::ParticlesManager::matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::rotate(angle, glm::vec3(x, y, z));
}

void Engine::ParticlesManager::matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::scale(glm::vec3(x, y, z));
}

void Engine::ParticlesManager::updateParticles(void)
{
	glEnable(GL_RASTERIZER_DISCARD);

	glUseProgram(_physicsProgram->getId());

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

void Engine::ParticlesManager::display(GBuffer *gbuf, Camera *cam) const
{
	gbuf->setParticlesState();

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

	struct
	{
		glm::vec3 ALIGN(16) position;
		glm::vec3 ALIGN(16) target;
	} camera;
	camera.position = cam->getCameraPosition();
	camera.target = cam->getTargetPosition();
	_cameraBuffer->updateStoreMap(&camera);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _cameraBuffer->getId());

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
