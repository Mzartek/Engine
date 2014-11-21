#include <Engine/MovableCamera.hpp>

Engine::MovableCamera::MovableCamera(void)
	: _speed(1), _atheta(0), _aphi(0)
{
	_vforward = new glm::vec3;
	_vleft = new glm::vec3;
}

Engine::MovableCamera::~MovableCamera(void)
{
	delete _vforward;
	delete _vleft;
}

void Engine::MovableCamera::setInitialAngle(const GLfloat &t, const GLfloat &p)
{
	_atheta = t;
	_aphi = p;

	if (_aphi >= glm::pi<GLfloat>() / 2) _aphi = 89.0f * glm::pi<GLfloat>() / 180;
	else if (_aphi <= -glm::pi<GLfloat>() / 2) _aphi = -89.0f * glm::pi<GLfloat>() / 180;

	GLfloat tmp = cos(_aphi);
	_vforward->x = tmp * sin(_atheta);
	_vforward->y = sin(_aphi);
	_vforward->z = tmp * cos(_atheta);

	_vleft->x = _vforward->z;
	_vleft->y = 0;
	_vleft->z = -_vforward->x;
	*_vleft = glm::normalize(*_vleft);

	*_ptarget = *_pcamera + *_vforward;
}

void Engine::MovableCamera::setSpeed(const GLfloat &v)
{
	_speed = v;
}

glm::vec3 Engine::MovableCamera::getVectorForward(void) const
{
	return *_vforward;
}

glm::vec3 Engine::MovableCamera::getVectorLeft(void) const
{
	return *_vleft;
}

void Engine::MovableCamera::mouseMove(const GLint &xrel, const GLint &yrel)
{
	_atheta -= (GLfloat)xrel * glm::pi<GLfloat>() / 180;
	_aphi -= (GLfloat)yrel * glm::pi<GLfloat>() / 180;

	if (_aphi >= glm::pi<GLfloat>() / 2) _aphi = 89.0f * glm::pi<GLfloat>() / 180;
	else if (_aphi <= -glm::pi<GLfloat>() / 2) _aphi = -89.0f * glm::pi<GLfloat>() / 180;

	GLfloat tmp = cos(_aphi);
	_vforward->x = tmp * sin(_atheta);
	_vforward->y = sin(_aphi);
	_vforward->z = tmp * cos(_atheta);

	_vleft->x = _vforward->z;
	_vleft->y = 0;
	_vleft->z = -_vforward->x;
	*_vleft = glm::normalize(*_vleft);

	*_ptarget = *_pcamera + *_vforward;
}
