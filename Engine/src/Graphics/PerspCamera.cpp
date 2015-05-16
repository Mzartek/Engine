#include <Engine/Graphics/PerspCamera.hpp>

Engine::PerspCamera::PerspCamera(void)
{
}

Engine::PerspCamera::~PerspCamera(void)
{
}

void Engine::PerspCamera::setCameraPosition(const glm::vec3 &pos)
{
	_pcamera = pos;
}

void Engine::PerspCamera::setAngle(GLfloat atheta, GLfloat aphi)
{
	GLfloat tmp = cosf(aphi);
	_vforward = glm::vec3(tmp * sinf(atheta), sinf(aphi), tmp * cosf(atheta));
	_vleft = glm::normalize(glm::vec3(_vforward.z, 0.0f, -_vforward.x));
	_vup = glm::cross(_vforward, _vleft);
}

void Engine::PerspCamera::setPositionAndTarget(const glm::vec3 &pos, const glm::vec3 &tar)
{
	_pcamera = pos;
	_vforward = glm::normalize(tar - pos);
	_vleft = glm::normalize(glm::vec3(_vforward.z, 0.0f, -_vforward.x));
	_vup = glm::cross(_vforward, _vleft);
}

void Engine::PerspCamera::setPerspective(GLfloat fov, GLuint width, GLuint height, GLfloat n, GLfloat f)
{
	GLfloat ratio = (GLfloat)width / height;
	GLfloat yfar = tanf(fov * 0.5f) * f;
	GLfloat xfar = yfar * ratio;

	_projectionMatrix = glm::perspective(fov, ratio, n, f);

	_near = n;
	_far = f;
	_fov = fov * ratio;
	_frusSphereDistance = n + (f - n) * 0.5f;
	_frusSphereRadius = glm::length(glm::vec3(xfar, yfar, f) - glm::vec3(0.0f, 0.0f, _frusSphereDistance));
}

const glm::vec3 &Engine::PerspCamera::getCameraPosition(void) const
{
	return _pcamera;
}

const glm::vec3 &Engine::PerspCamera::getForwardVector(void) const
{
	return _vforward;
}

const glm::vec3 &Engine::PerspCamera::getLeftVector(void) const
{
	return _vleft;
}

const glm::vec3 &Engine::PerspCamera::getUpVector(void) const
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

const glm::vec3 &Engine::PerspCamera::getFrusSpherePosition(void) const
{
	return _frusSpherePosition;
}

void Engine::PerspCamera::updateData(void)
{
	_frusSpherePosition = _vforward * _frusSphereDistance;

	_viewMatrix = glm::lookAt(_pcamera, _pcamera + _vforward, _vup);
	_VPMatrix = _projectionMatrix * _viewMatrix;
	_IVPMatrix = glm::inverse(_VPMatrix);
}