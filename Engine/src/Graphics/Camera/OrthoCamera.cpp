#include <Engine/Graphics/Camera/OrthoCamera.hpp>

Engine::Graphics::OrthoCamera::OrthoCamera(void)
{
	_cameraInfo.position = glm::vec3(0, 0, 0);
	_cameraInfo.direction = glm::vec3(1, 0, 0);

	_cameraInfoBuffer->createStore(GL_UNIFORM_BUFFER, &_cameraInfo, sizeof _cameraInfo, GL_DYNAMIC_DRAW);
}

Engine::Graphics::OrthoCamera::~OrthoCamera(void)
{
}

void Engine::Graphics::OrthoCamera::setPosition(const glm::vec3 &pos)
{
	_cameraInfo.position = pos;
}

void Engine::Graphics::OrthoCamera::setDirection(const glm::vec3 &dir)
{
	_cameraInfo.direction = dir;
}

void Engine::Graphics::OrthoCamera::setOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	_projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);

	_left = left;
	_right = right;
	_bottom = bottom;
	_top = top;
	_zNear = zNear;
	_zFar = zFar;
}

void Engine::Graphics::OrthoCamera::updateData(void)
{
	_viewMatrix = glm::lookAt(_cameraInfo.position - _cameraInfo.direction, _cameraInfo.position, glm::vec3(0.0f, 1.0f, 0.0f));
	_VPMatrix = _projectionMatrix * _viewMatrix;
	_IVPMatrix = glm::inverse(_VPMatrix);
}