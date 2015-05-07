#include <Engine/Graphics/Camera.hpp>

Engine::Camera::Camera(void)
{
	_projectionMatrix = std::shared_ptr<glm::mat4>(new glm::mat4);
	_viewMatrix = std::shared_ptr<glm::mat4>(new glm::mat4);
	_VPMatrix = std::shared_ptr<glm::mat4>(new glm::mat4);
	_IVPMatrix = std::shared_ptr<glm::mat4>(new glm::mat4);
}

Engine::Camera::~Camera(void)
{
}

const std::shared_ptr<glm::mat4> &Engine::Camera::getProjectionMatrix(void) const
{
	return _projectionMatrix;
}

const std::shared_ptr<glm::mat4> &Engine::Camera::getViewMatrix(void) const
{
	return _viewMatrix;
}

const std::shared_ptr<glm::mat4> &Engine::Camera::getVPMatrix(void) const
{
	return _VPMatrix;
}

const std::shared_ptr<glm::mat4> &Engine::Camera::getIVPMatrix(void) const
{
	return _IVPMatrix;
}
