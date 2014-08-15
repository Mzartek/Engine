#include <Engine/Light.hpp>

engine::Light::Light(void)
{
	_shadow = NULL;
	_lightPosition = new glm::vec3;
	_lightDirection = new glm::vec3;
	_lightColor = new glm::vec3;
	_projectionMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;
}

engine::Light::Light(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_shadow = NULL;
	_lightPosition = new glm::vec3(x, y, z);
	_lightDirection = new glm::vec3;
	_lightColor = new glm::vec3;
	_projectionMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;
}

engine::Light::~Light(void)
{
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	if (_shadow != NULL)
		delete _shadow;
	delete _lightPosition;
	delete _lightDirection;
	delete _lightColor;
	delete _projectionMatrix;
	delete _VPMatrix;
}

void engine::Light::configShadowMap(const GLuint &width, const GLuint &height, ShaderProgram *shadow)
{
	if (_shadow != NULL)
		delete _shadow;
	_shadow = new ShadowMap;
	_shadow->config(width, height, shadow);
}

void engine::Light::setPosition(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_lightPosition->x = x;
	_lightPosition->y = y;
	_lightPosition->z = z;
}

void engine::Light::setDirection(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_lightDirection->x = x;
	_lightDirection->y = y;
	_lightDirection->z = z;
}

void engine::Light::setColor(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_lightColor->x = x;
	_lightColor->y = y;
	_lightColor->z = z;
}

engine::ShadowMap *engine::Light::getShadowMap(void)
{
	return _shadow;
}

glm::vec3 engine::Light::getPosition(void) const
{
	return *_lightPosition;
}

glm::vec3 engine::Light::getDirection(void) const
{
	return *_lightDirection;
}

glm::vec3 engine::Light::getColor(void) const
{
	return *_lightColor;
}

glm::mat4 engine::Light::getProjectionMatrix(void) const
{
	return *_projectionMatrix;
}

glm::mat4 engine::Light::getVPMatrix(void) const
{
	return *_VPMatrix;
}

void engine::Light::clear(void) const
{
	if(_shadow==NULL)
	{
		std::cerr << "No need a newLoop for the light when you don't use shadowMapping" << std::endl;
		return;
	}
	_shadow->clear();
}
