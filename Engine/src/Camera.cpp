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
	_frusSpherePosition = new glm::vec3;
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
	delete _frusSpherePosition;
}

void Engine::Camera::setCameraPosition(const glm::vec3 &pos) const
{
	*_pcamera = pos;
}

void Engine::Camera::setTargetPosition(const glm::vec3 &pos) const
{
	*_ptarget = pos;
}

void Engine::Camera::setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f)
{
	GLfloat ratio = (GLfloat)width / height;
	GLfloat yfar = tanf(fov * 0.5f) * f;
	GLfloat xfar = yfar * ratio;

	*_projectionMatrix = glm::perspective(fov, ratio, n, f);

    _near = n;
    _far = f;
	_fov = fov * ratio;
	_frusSphereDistance = n + (f - n) * 0.5f;
	_frusSphereRadius = glm::length(glm::vec3(xfar, yfar, f) - glm::vec3(0.0f, 0.0f, _frusSphereDistance));
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

GLfloat Engine::Camera::getNear(void) const
{
    return _near;
}

GLfloat Engine::Camera::getFar(void) const
{
    return _far;
}

GLfloat Engine::Camera::getFOV(void) const
{
	return _fov;
}

GLfloat Engine::Camera::getFrusSphereDistance(void) const
{
    return _frusSphereDistance;
}

GLfloat Engine::Camera::getFrusSphereRadius(void) const
{
	return _frusSphereRadius;
}

glm::vec3 Engine::Camera::getFrusSpherePosition(void) const
{
	return *_frusSpherePosition;
}

void Engine::Camera::position(void) const
{
	*_vview = glm::normalize(*_ptarget - *_pcamera);
	*_frusSpherePosition = *_vview * _frusSphereDistance;
	*_viewMatrix = glm::lookAt(*_pcamera, *_ptarget, glm::vec3(0.0f, 1.0f, 0.0f));
	*_VPMatrix = *_projectionMatrix * *_viewMatrix;
	*_IVPMatrix = glm::inverse(*_VPMatrix);
}
