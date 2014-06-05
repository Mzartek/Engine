#include <Engine/Camera.hpp>

engine::Camera::Camera(void)
{
	_pcamera = new Vector3D<GLfloat>;
	_ptarget = new Vector3D<GLfloat>;
	_pcamera->x = 0;
	_pcamera->y = 0;
	_pcamera->z = 0;
}

engine::Camera::Camera(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_pcamera = new Vector3D<GLfloat>;
	_ptarget = new Vector3D<GLfloat>;
	_pcamera->x = x;
	_pcamera->y = y;
	_pcamera->z = z;
}

engine::Camera::~Camera(void)
{
	delete _pcamera;
	delete _ptarget;
}

void engine::Camera::setPositionCamera(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_pcamera->x = x;
	_pcamera->y = y;
	_pcamera->z = z;
}

void engine::Camera::setPositionTarget(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_ptarget->x = x;
	_ptarget->y = y;
	_ptarget->z = z;
}

void engine::Camera::setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f)
{
	_width = width;
	_height = height;
	matrixPerspective(_projectionMatrix, fov, (GLfloat)_width / (GLfloat)_height, n, f);
}

engine::Vector3D<GLfloat> *engine::Camera::getPositionCamera(void) const
{
	return _pcamera;
}

engine::Vector3D<GLfloat> *engine::Camera::getPositionTarget(void) const
{
	return _ptarget;
}

GLuint engine::Camera::getWidth(void) const
{
	return _width;
}

GLuint engine::Camera::getHeight(void) const
{
	return _height;
}

GLfloat *engine::Camera::getMatrix(void)
{
	return _VP;
}

void engine::Camera::position(void)
{
	GLfloat camera[] = {_pcamera->x, _pcamera->y, _pcamera->z};
	GLfloat target[] = {_ptarget->x, _ptarget->y, _ptarget->z};
	GLfloat head[] = {0.0, 1.0, 0.0};
	GLfloat view[16];

	matrixLoadIdentity(view);
	matrixLookAt(view, camera, target, head);
	matrixMultiply(_VP, _projectionMatrix, view);
}
