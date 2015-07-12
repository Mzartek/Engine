#include <Engine/Graphics/FreeCam.hpp>

Engine::Graphics::FreeCam::FreeCam(void)
{
}

Engine::Graphics::FreeCam::FreeCam(GLfloat atheta, GLfloat aphi)
	: MovableCamera(atheta, aphi)
{
}

Engine::Graphics::FreeCam::~FreeCam(void)
{
}

void Engine::Graphics::FreeCam::keyboardMove(GLboolean f, GLboolean b, GLboolean l, GLboolean r)
{
	if (f)
		_cameraInfo.position += _cameraInfo.forward * _speed;
	if (b)
		_cameraInfo.position -= _cameraInfo.forward * _speed;
	if (l)
		_cameraInfo.position += _cameraInfo.left * _speed;
	if (r)
		_cameraInfo.position -= _cameraInfo.left * _speed;
}
