#include <Engine/Graphics/Camera/PerspCamera.hpp>

Engine::Graphics::PerspCamera::PerspCamera(void)
{
	_cameraInfo.position = glm::vec3(0, 0, 0);
	_cameraInfo.forward = glm::vec3(0, 0, 1);
	_cameraInfo.left = glm::normalize(glm::vec3(_cameraInfo.forward.z, 0.0f, -_cameraInfo.forward.x));
	_cameraInfo.up = glm::cross(_cameraInfo.forward, _cameraInfo.left);

	_cameraInfoBuffer->createStore(GL_UNIFORM_BUFFER, &_cameraInfo, sizeof _cameraInfo, GL_DYNAMIC_DRAW);
}

Engine::Graphics::PerspCamera::~PerspCamera(void)
{
}

void Engine::Graphics::PerspCamera::setCameraPosition(const glm::vec3 &pos)
{
	_cameraInfo.position = pos;
}

void Engine::Graphics::PerspCamera::setAngle(GLfloat atheta, GLfloat aphi)
{
	GLfloat tmp = cosf(aphi);
	_cameraInfo.forward = glm::vec3(tmp * sinf(atheta), sinf(aphi), tmp * cosf(atheta));
	_cameraInfo.left = glm::normalize(glm::vec3(_cameraInfo.forward.z, 0.0f, -_cameraInfo.forward.x));
	_cameraInfo.up = glm::cross(_cameraInfo.forward, _cameraInfo.left);
}

void Engine::Graphics::PerspCamera::setPositionAndTarget(const glm::vec3 &pos, const glm::vec3 &tar)
{
	_cameraInfo.position = pos;
	_cameraInfo.forward = glm::normalize(tar - pos);
	_cameraInfo.left = glm::normalize(glm::vec3(_cameraInfo.forward.z, 0.0f, -_cameraInfo.forward.x));
	_cameraInfo.up = glm::cross(_cameraInfo.forward, _cameraInfo.left);
}

void Engine::Graphics::PerspCamera::setPerspective(GLfloat fov, GLuint width, GLuint height, GLfloat n, GLfloat f)
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

const glm::vec3 &Engine::Graphics::PerspCamera::getCameraPosition(void) const
{
	return _cameraInfo.position;
}

const glm::vec3 &Engine::Graphics::PerspCamera::getForwardVector(void) const
{
	return _cameraInfo.forward;
}

const glm::vec3 &Engine::Graphics::PerspCamera::getLeftVector(void) const
{
	return _cameraInfo.left;
}

const glm::vec3 &Engine::Graphics::PerspCamera::getUpVector(void) const
{
	return _cameraInfo.up;
}

GLfloat Engine::Graphics::PerspCamera::getNear(void) const
{
	return _near;
}

GLfloat Engine::Graphics::PerspCamera::getFar(void) const
{
	return _far;
}

GLfloat Engine::Graphics::PerspCamera::getFOV(void) const
{
	return _fov;
}

GLfloat Engine::Graphics::PerspCamera::getFrusSphereDistance(void) const
{
	return _frusSphereDistance;
}

GLfloat Engine::Graphics::PerspCamera::getFrusSphereRadius(void) const
{
	return _frusSphereRadius;
}

const glm::vec3 &Engine::Graphics::PerspCamera::getFrusSpherePosition(void) const
{
	return _frusSpherePosition;
}

void Engine::Graphics::PerspCamera::updateData(void)
{
	_frusSpherePosition = _cameraInfo.forward * _frusSphereDistance;

	_viewMatrix = glm::lookAt(_cameraInfo.position, _cameraInfo.position + _cameraInfo.forward, _cameraInfo.up);
	_VPMatrix = _projectionMatrix * _viewMatrix;
	_IVPMatrix = glm::inverse(_VPMatrix);

	_cameraInfoBuffer->updateStoreMap(&_cameraInfo);
}