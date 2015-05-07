#include <Engine/Graphics/PerspCamera.hpp>

Engine::PerspCamera::PerspCamera(void)
{
	_pcamera = std::shared_ptr<glm::vec3>(new glm::vec3);
	_vforward = std::shared_ptr<glm::vec3>(new glm::vec3);
	_vleft = std::shared_ptr<glm::vec3>(new glm::vec3);
	_vup = std::shared_ptr<glm::vec3>(new glm::vec3);

	_frusSpherePosition = std::shared_ptr<glm::vec3>(new glm::vec3);
}

Engine::PerspCamera::~PerspCamera(void)
{
}

void Engine::PerspCamera::setCameraPosition(const std::shared_ptr<glm::vec3> &pos)
{
	*_pcamera = *pos;
}

void Engine::PerspCamera::setTargetPosition(GLfloat atheta, GLfloat aphi) const
{
	GLfloat tmp = cosf(aphi);
	*_vforward = glm::vec3(tmp * sinf(atheta), sinf(aphi), tmp * cosf(atheta));
	*_vleft = glm::normalize(glm::vec3(_vforward->z, 0.0f, -_vforward->x));
	*_vup = glm::cross(*_vforward, *_vleft);
}

void Engine::PerspCamera::setPerspective(GLfloat fov, GLuint width, GLuint height, GLfloat n, GLfloat f)
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

const std::shared_ptr<glm::vec3> &Engine::PerspCamera::getCameraPosition(void) const
{
	return _pcamera;
}

const std::shared_ptr<glm::vec3> &Engine::PerspCamera::getForwardVector(void) const
{
	return _vforward;
}

const std::shared_ptr<glm::vec3> &Engine::PerspCamera::getLeftVector(void) const
{
	return _vleft;
}

const std::shared_ptr<glm::vec3> &Engine::PerspCamera::getUpVector(void) const
{
	return _vup;
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

const std::shared_ptr<glm::vec3> &Engine::PerspCamera::getFrusSpherePosition(void) const
{
	return _frusSpherePosition;
}

void Engine::PerspCamera::position(void) const
{
	*_frusSpherePosition = *_vforward * _frusSphereDistance;

	*_viewMatrix = glm::lookAt(*_pcamera, *_pcamera + *_vforward, *_vup);
	*_VPMatrix = *_projectionMatrix * *_viewMatrix;
	*_IVPMatrix = glm::inverse(*_VPMatrix);
}