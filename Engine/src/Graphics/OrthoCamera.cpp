#include <Engine/Graphics/OrthoCamera.hpp>

Engine::OrthoCamera::OrthoCamera(void)
{
}

Engine::OrthoCamera::~OrthoCamera(void)
{
}

void Engine::OrthoCamera::setPosition(const glm::vec3 &pos)
{
	_position = pos;
}

void Engine::OrthoCamera::setDirection(const glm::vec3 &dir)
{
	_direction = dir;
}

void Engine::OrthoCamera::setOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	_projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);

	_left = left;
	_right = right;
	_bottom = bottom;
	_top = top;
	_zNear = zNear;
	_zFar = zFar;
}

void Engine::OrthoCamera::position(void)
{
	_viewMatrix = glm::lookAt(_position - _direction, _position, glm::vec3(0.0f, 1.0f, 0.0f));
	_VPMatrix = _projectionMatrix * _viewMatrix;
	_IVPMatrix = glm::inverse(_VPMatrix);
}