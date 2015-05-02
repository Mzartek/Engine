#include <Engine/PerspCamera.hpp>
#include <Engine/tools/ControllerMemory.hpp>

Engine::PerspCamera::PerspCamera(void)
{
	_pcamera = new_ref(glm::vec3);
	_vforward = new_ref(glm::vec3);
	_vleft = new_ref(glm::vec3);
	_vup = new_ref(glm::vec3);

	_frusSpherePosition = new_ref(glm::vec3);
}

Engine::PerspCamera::~PerspCamera(void)
{
	release_ref(_pcamera);
	release_ref(_vforward);
	release_ref(_vleft);
	release_ref(_vup);

	release_ref(_frusSpherePosition);
}

void Engine::PerspCamera::setCameraPosition(const glm::vec3 &pos) const
{
	*_pcamera = pos;
}

void Engine::PerspCamera::setTargetPosition(const GLfloat &atheta, const GLfloat &aphi) const
{
	GLfloat tmp = cosf(aphi);
	*_vforward = glm::vec3(tmp * sinf(atheta), sinf(aphi), tmp * cosf(atheta));
	*_vleft = glm::normalize(glm::vec3(_vforward->z, 0.0f, -_vforward->x));
	*_vup = glm::cross(*_vforward, *_vleft);
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

glm::vec3 Engine::PerspCamera::getForwardVector(void) const
{
	return *_vforward;
}

glm::vec3 Engine::PerspCamera::getLeftVector(void) const
{
	return *_vleft;
}

glm::vec3 Engine::PerspCamera::getUpVector(void) const
{
	return *_vup;
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
	*_frusSpherePosition = *_vforward * _frusSphereDistance;

	*_viewMatrix = glm::lookAt(*_pcamera, *_pcamera + *_vforward, *_vup);
	*_VPMatrix = *_projectionMatrix * *_viewMatrix;
	*_IVPMatrix = glm::inverse(*_VPMatrix);
}