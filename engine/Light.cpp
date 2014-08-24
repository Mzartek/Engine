#include <Engine/Light.hpp>

engine::Light::Light(void)
{
	_VPMatrix = new glm::mat4;
	_shadow = NULL;
}

engine::Light::~Light(void)
{
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	if (glIsBuffer(_idLightInfoBuffer))
		glDeleteBuffers(1, &_idLightInfoBuffer);

	delete _VPMatrix;
	if (_shadow != NULL)
		delete _shadow;
}

void engine::Light::configShadowMap(const GLuint &width, const GLuint &height, ShaderProgram *shadow)
{
	if (_shadow != NULL)
		delete _shadow;
	_shadow = new ShadowMap;
	_shadow->config(width, height, shadow);
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
	if(_shadow==NULL)
	{
		std::cerr << "Need to config the ShadowMap before clearing" << std::endl;
		exit(1);
	}
	_shadow->clear();
}
