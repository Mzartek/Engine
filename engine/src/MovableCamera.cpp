#include <Engine/MovableCamera.hpp>

engine::MovableCamera::MovableCamera(void)
	: _speed(1), _atheta(0), _aphi(0)
{
	_vforward = new glm::vec3;
	_vleft = new glm::vec3;
}

engine::MovableCamera::~MovableCamera(void)
{
	delete _vforward;
	delete _vleft;
}

void engine::MovableCamera::setInitialAngle(const GLfloat &t, const GLfloat &p)
{
	_atheta = t;
	_aphi = p;

	if (_atheta > 360)
		_atheta -= 360;
	else if (_atheta < -360)
		_atheta += 360;
	if (_aphi > 89)
		_aphi = 89;
	else if (_aphi < -89)
		_aphi = -89;

	GLfloat tmp = (GLfloat)cos(_aphi*M_PI / 180);
	_vforward->x = tmp*(GLfloat)sin(_atheta*M_PI / 180);
	_vforward->y = (GLfloat)sin(_aphi*M_PI / 180);
	_vforward->z = tmp*(GLfloat)cos(_atheta*M_PI / 180);

	_vleft->x = _vforward->z;
	_vleft->y = 0;
	_vleft->z = -_vforward->x;
	*_vleft = glm::normalize(*_vleft);

	*_ptarget = *_pcamera + *_vforward;
}

void engine::MovableCamera::setSpeed(const GLfloat &v)
{
	_speed = v;
}

glm::vec3 engine::MovableCamera::getForward(void) const
{
	return *_vforward;
}

glm::vec3 engine::MovableCamera::getLeft(void) const
{
	return *_vleft;
}

void engine::MovableCamera::mouseMove(const GLint &xrel, const GLint &yrel)
{
	_atheta -= (GLfloat)xrel;
	_aphi -= (GLfloat)yrel;

	if (_atheta > 360)
		_atheta -= 360;
	else if (_atheta < -360)
		_atheta += 360;
	if (_aphi > 89)
		_aphi = 89;
	else if (_aphi < -89)
		_aphi = -89;

	GLfloat tmp = (GLfloat)cos(_aphi*M_PI / 180);
	_vforward->x = tmp*(GLfloat)sin(_atheta*M_PI / 180);
	_vforward->y = (GLfloat)sin(_aphi*M_PI / 180);
	_vforward->z = tmp*(GLfloat)cos(_atheta*M_PI / 180);

	_vleft->x = _vforward->z;
	_vleft->y = 0;
	_vleft->z = -_vforward->x;
	*_vleft = glm::normalize(*_vleft);

	*_ptarget = *_pcamera + *_vforward;
}