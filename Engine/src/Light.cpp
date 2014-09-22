#include <Engine/Light.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>

engine::Light::Light(void)
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

engine::Light::~Light(void)
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

void engine::Light::configShadowMap(const GLuint &width, const GLuint &height)
{
	_shadow->config(width, height);
}

glm::mat4 engine::Light::getVPMatrix(void) const
{
	return *_VPMatrix;
}

engine::ShadowMap *engine::Light::getShadowMap(void)
{
	return _shadow;
}

void engine::Light::clear(void) const
{
	_shadow->clear();
}
