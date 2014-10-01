#include <Engine/Light.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>

Engine::Light::Light(void)
{
	_vertexBuffer = new Buffer;
	_shadowMatrixBuffer = new Buffer;
	_IVPMatrixBuffer = new Buffer;
	_screenBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_lightInfoBuffer = new Buffer;
	_shadow = new ShadowMap;
	_VPMatrix = new glm::mat4;

	GLfloat vertex[] = 
	{
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
}

Engine::Light::~Light(void)
{
	delete _vertexBuffer;
	delete _shadowMatrixBuffer;
	delete _IVPMatrixBuffer;
	delete _screenBuffer;
	delete _cameraBuffer;
	delete _lightInfoBuffer;
	delete _shadow;
	delete _VPMatrix;
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
