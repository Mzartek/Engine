#include <Engine/Camera.hpp>

engine::Camera::Camera(void)
{
	_pcamera = new glm::vec3;
	_ptarget = new glm::vec3;
	_projectionMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;

	_pcamera->x = 0;
	_pcamera->y = 0;
	_pcamera->z = 0;
}

engine::Camera::Camera(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_pcamera = new glm::vec3;
	_ptarget = new glm::vec3;
	_projectionMatrix = new glm::mat4;
	_VPMatrix = new glm::mat4;

	_pcamera->x = x;
	_pcamera->y = y;
	_pcamera->z = z;
}

engine::Camera::~Camera(void)
{
	delete _pcamera;
	delete _ptarget;
	delete _projectionMatrix;
	delete _VPMatrix;
}

void engine::Camera::setPositionCamera(const glm::vec3 &pos)
{
	*_pcamera = pos;
}

void engine::Camera::setPositionTarget(const glm::vec3 &pos)
{
	*_ptarget = pos;
}

void engine::Camera::setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f)
{
	*_projectionMatrix = glm::perspective(fov * ((GLfloat)M_PI / 180), (GLfloat)width / height, n, f);
}

glm::vec3 engine::Camera::getPositionCamera(void) const
{
	return *_pcamera;
}

glm::vec3 engine::Camera::getPositionTarget(void) const
{
	return *_ptarget;
}

glm::mat4 engine::Camera::getProjectionMatrix(void) const
{
	return *_projectionMatrix;
}

glm::mat4 engine::Camera::getVPMatrix(void) const
{
	return *_VPMatrix;
}

void engine::Camera::position(void)
{
	*_VPMatrix = *_projectionMatrix * glm::lookAt(*_pcamera, *_ptarget, glm::vec3(0.0f, 1.0f, 0.0f));
}
