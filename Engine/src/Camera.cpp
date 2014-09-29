#include <Engine/Camera.hpp>

Engine::Camera::Camera(void)
{
	_pcamera = new glm::vec3;
	_ptarget = new glm::vec3;
	_projectionMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;
}

Engine::Camera::~Camera(void)
{
	delete _pcamera;
	delete _ptarget;
	delete _projectionMatrix;
	delete _VPMatrix;
}

void Engine::Camera::setPositionCamera(const glm::vec3 &pos)
{
	*_pcamera = pos;
}

void Engine::Camera::setPositionTarget(const glm::vec3 &pos)
{
	*_ptarget = pos;
}

void Engine::Camera::setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f)
{
	*_projectionMatrix = glm::perspective(fov * ((GLfloat)M_PI / 180), (GLfloat)width / height, n, f);
}

glm::vec3 Engine::Camera::getPositionCamera(void) const
{
	return *_pcamera;
}

glm::vec3 Engine::Camera::getPositionTarget(void) const
{
	return *_ptarget;
}

glm::mat4 Engine::Camera::getProjectionMatrix(void) const
{
	return *_projectionMatrix;
}

glm::mat4 Engine::Camera::getVPMatrix(void) const
{
	return *_VPMatrix;
}

void Engine::Camera::position(void)
{
	*_VPMatrix = *_projectionMatrix * glm::lookAt(*_pcamera, *_ptarget, glm::vec3(0.0f, 1.0f, 0.0f));
}
