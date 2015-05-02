#include <Engine/Camera.hpp>
#include <Engine/tools/ControllerMemory.hpp>

Engine::Camera::Camera(void)
{
	_projectionMatrix = new_ref(glm::mat4);
	_viewMatrix = new_ref(glm::mat4);
	_VPMatrix = new_ref(glm::mat4);
	_IVPMatrix = new_ref(glm::mat4);
}

Engine::Camera::~Camera(void)
{
	release_ref(_projectionMatrix);
	release_ref(_viewMatrix);
	release_ref(_VPMatrix);
	release_ref(_IVPMatrix);
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
