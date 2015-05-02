#include <Engine/OrthoCamera.hpp>
#include <Engine/tools/ControllerMemory.hpp>

Engine::OrthoCamera::OrthoCamera(void)
{
	_position = new_ref(glm::vec3);
	_direction = new_ref(glm::vec3);
}

Engine::OrthoCamera::~OrthoCamera(void)
{
	release_ref(_position);
	release_ref(_direction);
}

void Engine::OrthoCamera::setPosition(const glm::vec3 &pos) const
{
	*_position = pos;
}

void Engine::OrthoCamera::setDirection(const glm::vec3 &dir) const
{
	*_direction = dir;
}

void Engine::OrthoCamera::setOrthogonal(const GLfloat &left, const GLfloat &right, const GLfloat &bottom, const GLfloat &top, const GLfloat &zNear, const GLfloat &zFar)
{
	*_projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);

	_left = left;
	_right = right;
	_bottom = bottom;
	_top = top;
	_zNear = zNear;
	_zFar = zFar;
}

void Engine::OrthoCamera::position(void) const
{
	*_viewMatrix = glm::lookAt(*_position - *_direction, *_position, glm::vec3(0.0f, 1.0f, 0.0f));
	*_VPMatrix = *_projectionMatrix * *_viewMatrix;
	*_IVPMatrix = glm::inverse(*_VPMatrix);
}