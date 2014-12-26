#include <Engine/Camera.hpp>

Engine::Camera::Camera(void)
{
	_pcamera = new glm::vec3;
	_ptarget = new glm::vec3;
	_vview = new glm::vec3;
	_projectionMatrix = new glm::mat4;
	_viewMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;
	_IVPMatrix = new glm::mat4;
}

Engine::Camera::~Camera(void)
{
	delete _pcamera;
	delete _ptarget;
	delete _vview;
	delete _projectionMatrix;
	delete _viewMatrix;
	delete _VPMatrix;
	delete _IVPMatrix;
}

void Engine::Camera::setCameraPosition(const glm::vec3 &pos)
{
	*_pcamera = pos;
}

void Engine::Camera::setTargetPosition(const glm::vec3 &pos)
{
	*_ptarget = pos;
}

void Engine::Camera::setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f)
{
	*_projectionMatrix = glm::perspective(fov, (GLfloat)width / height, n, f);

	_fov = fov * width / height;
	_viewLen = f - n;
	_frusSphereRadius = glm::length(glm::vec3(0.0f, 0.0f, n + _viewLen * 0.5f) - glm::vec3(width, height, _viewLen));
}

glm::vec3 Engine::Camera::getCameraPosition(void) const
{
	return *_pcamera;
}

glm::vec3 Engine::Camera::getTargetPosition(void) const
{
	return *_ptarget;
}

glm::vec3 Engine::Camera::getViewVector(void) const
{
	return *_vview;
}

glm::mat4 Engine::Camera::getProjectionMatrix(void) const
{
	return *_projectionMatrix;
}

glm::mat4 Engine::Camera::getViewMatrix(void) const
{
	return *_viewMatrix;
}

glm::mat4 Engine::Camera::getVPMatrix(void) const
{
	return *_VPMatrix;
}

glm::mat4 Engine::Camera::getIVPMatrix(void) const
{
	return *_IVPMatrix;
}

GLfloat Engine::Camera::getFOV(void) const
{
	return _fov;
}

GLfloat Engine::Camera::getFrusSphereRadius(void) const
{
	return _frusSphereRadius;
}

void Engine::Camera::position(void)
{
	*_vview = glm::normalize(*_ptarget - *_pcamera);
	*_viewMatrix = glm::lookAt(*_pcamera, *_ptarget, glm::vec3(0.0f, 1.0f, 0.0f));
	*_VPMatrix = *_projectionMatrix * *_viewMatrix;
	*_IVPMatrix = glm::inverse(*_VPMatrix);
}
