#include <Engine/PerspCamera.hpp>

Engine::PerspCamera::PerspCamera(void)
{
	_pcamera = new glm::vec3;
	_ptarget = new glm::vec3;
	_vview = new glm::vec3;
	_frusSpherePosition = new glm::vec3;
}

Engine::PerspCamera::~PerspCamera(void)
{
	delete _pcamera;
	delete _ptarget;
	delete _vview;
	delete _frusSpherePosition;
}

void Engine::PerspCamera::setCameraPosition(const glm::vec3 &pos) const
{
	*_pcamera = pos;
}

void Engine::PerspCamera::setTargetPosition(const glm::vec3 &pos) const
{
	*_ptarget = pos;
}

void Engine::PerspCamera::setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f)
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

glm::vec3 Engine::PerspCamera::getCameraPosition(void) const
{
	return *_pcamera;
}

glm::vec3 Engine::PerspCamera::getTargetPosition(void) const
{
	return *_ptarget;
}

glm::vec3 Engine::PerspCamera::getViewVector(void) const
{
	return *_vview;
}

GLfloat Engine::PerspCamera::getNear(void) const
{
	return _near;
}

GLfloat Engine::PerspCamera::getFar(void) const
{
	return _far;
}

GLfloat Engine::PerspCamera::getFOV(void) const
{
	return _fov;
}

GLfloat Engine::PerspCamera::getFrusSphereDistance(void) const
{
	return _frusSphereDistance;
}

GLfloat Engine::PerspCamera::getFrusSphereRadius(void) const
{
	return _frusSphereRadius;
}

glm::vec3 Engine::PerspCamera::getFrusSpherePosition(void) const
{
	return *_frusSpherePosition;
}

void Engine::PerspCamera::position(void) const
{
	*_vview = glm::normalize(*_ptarget - *_pcamera);
	*_frusSpherePosition = *_vview * _frusSphereDistance;
	*_viewMatrix = glm::lookAt(*_pcamera, *_ptarget, glm::vec3(0.0f, 1.0f, 0.0f));
	*_VPMatrix = *_projectionMatrix * *_viewMatrix;
	*_IVPMatrix = glm::inverse(*_VPMatrix);
}