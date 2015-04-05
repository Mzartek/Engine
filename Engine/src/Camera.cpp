#include <Engine/Camera.hpp>

Engine::Camera::Camera(void)
{
	_projectionMatrix = new glm::mat4;
	_viewMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;
	_IVPMatrix = new glm::mat4;
}

Engine::Camera::~Camera(void)
{
	delete _projectionMatrix;
	delete _viewMatrix;
	delete _VPMatrix;
	delete _IVPMatrix;
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
