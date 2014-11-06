#include <Engine/Light.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>

Engine::Light::Light(void)
{
	_vertexBuffer = new Buffer;
	_mainInfoBuffer = new Buffer;
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
	_mainInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 160, GL_DYNAMIC_DRAW);
}

Engine::Light::~Light(void)
{
	delete _vertexBuffer;
	delete _mainInfoBuffer;
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
