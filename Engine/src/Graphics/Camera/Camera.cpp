#include <Engine/Graphics/Camera/Camera.hpp>

Engine::Graphics::Camera::Camera(void)
{
	_cameraInfoBuffer = std::make_shared<Buffer>();
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

const std::shared_ptr<Engine::Graphics::Buffer> &Engine::Graphics::Camera::getCameraInfoBuffer(void) const
{
	return _cameraInfoBuffer;
}