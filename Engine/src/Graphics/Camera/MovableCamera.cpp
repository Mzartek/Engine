#include <Engine/Graphics/Camera/MovableCamera.hpp>

Engine::Graphics::MovableCamera::MovableCamera(void)
	: _speed(1), _atheta(0), _aphi(0)
{
}

Engine::Graphics::MovableCamera::MovableCamera(GLfloat atheta, GLfloat aphi)
	: _speed(1), _atheta(atheta), _aphi(aphi)
{
}

Engine::Graphics::MovableCamera::~MovableCamera(void)
{
}

void Engine::Graphics::MovableCamera::setSpeed(GLfloat v)
{
	_speed = v;
}

void Engine::Graphics::MovableCamera::mouseMove(GLint xrel, GLint yrel)
{
	_atheta -= (GLfloat)xrel * glm::pi<GLfloat>() / 180;
	_aphi -= (GLfloat)yrel * glm::pi<GLfloat>() / 180;

	if (_aphi >= glm::pi<GLfloat>() / 2) _aphi = 89.0f * glm::pi<GLfloat>() / 180;
	else if (_aphi <= -glm::pi<GLfloat>() / 2) _aphi = -89.0f * glm::pi<GLfloat>() / 180;

	this->setAngle(_atheta, _aphi);
}
