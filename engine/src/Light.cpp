#include <Engine/Light.hpp>
#include <Engine/ShadowMap.hpp>

engine::Light::Light(void)
	: _idVAO(0), _idVBO(0), _idLightInfoBuffer(0)
{
	_VPMatrix = new glm::mat4;
	_shadow = new ShadowMap;
}

engine::Light::~Light(void)
{
	if (glIsVertexArray(_idVAO)) glDeleteVertexArrays(1, &_idVAO);
	if (glIsBuffer(_idVBO)) glDeleteBuffers(1, &_idVBO);
	if (glIsBuffer(_idLightInfoBuffer)) glDeleteBuffers(1, &_idLightInfoBuffer);
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
