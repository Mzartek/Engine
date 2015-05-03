#include <Engine/Graphics/Camera.hpp>

Engine::Camera::Camera(void)
{
	_projectionMatrix = new_ptr(glm::mat4);
	_viewMatrix = new_ptr(glm::mat4);
	_VPMatrix = new_ptr(glm::mat4);
	_IVPMatrix = new_ptr(glm::mat4);
}

Engine::Camera::~Camera(void)
{
	release_ptr(_projectionMatrix);
	release_ptr(_viewMatrix);
	release_ptr(_VPMatrix);
	release_ptr(_IVPMatrix);
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
