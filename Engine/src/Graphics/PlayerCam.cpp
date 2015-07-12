#include <Engine/Graphics/PlayerCam.hpp>

Engine::Graphics::PlayerCam::PlayerCam(void)
{
}

Engine::Graphics::PlayerCam::PlayerCam(GLfloat atheta, GLfloat aphi)
	: MovableCamera(atheta, aphi)
{
}

Engine::Graphics::PlayerCam::~PlayerCam(void)
{
}

void Engine::Graphics::PlayerCam::keyboardMove(GLboolean f, GLboolean b, GLboolean l, GLboolean r)
{
	if (f)
	{
		_cameraInfo.position.x -= _cameraInfo.left.z * _speed;
		_cameraInfo.position.z += _cameraInfo.left.x * _speed;
	}
	if (b)
	{
		_cameraInfo.position.x += _cameraInfo.left.z * _speed;
		_cameraInfo.position.z -= _cameraInfo.left.x * _speed;
	}
	if (l)
		_cameraInfo.position += _cameraInfo.left * _speed;
	if (r)
		_cameraInfo.position -= _cameraInfo.left * _speed;
}
