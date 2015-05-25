#include <Engine/Graphics/Camera.hpp>

Engine::Graphics::Camera::Camera(void)
{
}

Engine::Graphics::Camera::~Camera(void)
{
}

const glm::mat4 &Engine::Graphics::Camera::getProjectionMatrix(void) const
{
	return _projectionMatrix;
}

const glm::mat4 &Engine::Graphics::Camera::getViewMatrix(void) const
{
	return _viewMatrix;
}

const glm::mat4 &Engine::Graphics::Camera::getVPMatrix(void) const
{
	return _VPMatrix;
}

const glm::mat4 &Engine::Graphics::Camera::getIVPMatrix(void) const
{
	return _IVPMatrix;
}
