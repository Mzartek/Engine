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
		_pcamera.x -= _vleft.z * _speed;
		_pcamera.z += _vleft.x * _speed;
	}
	if (b)
	{
		_pcamera.x += _vleft.z * _speed;
		_pcamera.z -= _vleft.x * _speed;
	}
	if (l)
		_pcamera += _vleft * _speed;
	if (r)
		_pcamera -= _vleft * _speed;
}
