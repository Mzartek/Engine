#include <Engine/Light.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>

Engine::Light::Light(void)
{
	glGenVertexArrays(1, &_idVAO);
	_vertexBuffer = new Buffer;
	_shadowMatrixBuffer = new Buffer;
	_IVPMatrixBuffer = new Buffer;
	_screenBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_lightInfoBuffer = new Buffer;
	_VPMatrix = new glm::mat4;
	_shadow = new ShadowMap;
}

Engine::Light::~Light(void)
{
	glDeleteVertexArrays(1, &_idVAO);
	delete _vertexBuffer;
	delete _shadowMatrixBuffer;
	delete _IVPMatrixBuffer;
	delete _screenBuffer;
	delete _cameraBuffer;
	delete _lightInfoBuffer;
	delete _VPMatrix;
	delete _shadow;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void Engine::Light::config(ShaderProgram *program)
{
	_program = program;

	// Layout
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);
	_shadowMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	_IVPMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	_screenBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 16, GL_DYNAMIC_DRAW);
	_cameraBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 16, GL_DYNAMIC_DRAW);

	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void Engine::Light::configShadowMap(const GLuint &width, const GLuint &height)
{
	_shadow->config(width, height);
}

glm::mat4 Engine::Light::getVPMatrix(void) const
{
	return *_VPMatrix;
}

Engine::ShadowMap *Engine::Light::getShadowMap(void)
{
	return _shadow;
}

void Engine::Light::clear(void) const
{
	_shadow->clear();
}
