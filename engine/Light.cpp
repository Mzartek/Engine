#include <Engine/Light.hpp>

engine::Light::Light(void)
{
	_lightPosition[0] = 0;
	_lightPosition[1] = 0;
	_lightPosition[2] = 0;
	_lightColor[0]=1.0;
	_lightColor[1]=1.0;
	_lightColor[2]=1.0;
	_lightDirection[0] = 1.0;
	_lightDirection[1] = 0;
	_lightDirection[2] = 0;
	_shadow = NULL;
}

engine::Light::Light(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_lightPosition[0] = x;
	_lightPosition[1] = y;
	_lightPosition[2] = z;
	_lightColor[0]=1.0;
	_lightColor[1]=1.0;
	_lightColor[2]=1.0;
	_lightDirection[0] = 1.0;
	_lightDirection[1] = 0;
	_lightDirection[2] = 0;
	_shadow = NULL;
}

engine::Light::~Light(void)
{
	if(_shadow!=NULL)
		delete _shadow;
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
}

void engine::Light::configShadowMap(const GLuint &width, const GLuint &height, ShaderProgram *shadow)
{
	if(_shadow!=NULL)
		delete _shadow;
	_shadow = new ShadowMap;
	_shadow->config(width, height, shadow);
}

void engine::Light::setPosition(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_lightPosition[0] = x;
	_lightPosition[1] = y;
	_lightPosition[2] = z;
}

void engine::Light::setDirection(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_lightDirection[0] = x;
	_lightDirection[1] = y;
	_lightDirection[2] = z;
}

void engine::Light::setColor(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_lightColor[0] = x;
	_lightColor[1] = y;
	_lightColor[2] = z;
}

GLfloat *engine::Light::getPosition(void)
{
	return _lightPosition;
}

GLfloat *engine::Light::getDirection(void)
{
	return _lightDirection;
}

GLfloat *engine::Light::getColor(void)
{
	return _lightColor;
}

engine::ShadowMap *engine::Light::getShadowMap(void)
{
	return _shadow;
}
GLfloat *engine::Light::getMatrix(void)
{
	return _VP;
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
