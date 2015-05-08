#include <Engine/Graphics/PlayerCam.hpp>

Engine::PlayerCam::PlayerCam(void)
{
}

Engine::PlayerCam::PlayerCam(GLfloat atheta, GLfloat aphi)
    : MovableCamera(atheta, aphi)
{
}

Engine::PlayerCam::~PlayerCam(void)
{
}

void Engine::PlayerCam::keyboardMove(GLboolean f, GLboolean b, GLboolean l, GLboolean r)
{
	if(f)
	{
		_pcamera.x -= _vleft.z * _speed;
		_pcamera.z += _vleft.x * _speed;
	}
	if(b)
	{
		_pcamera.x += _vleft.z * _speed;
		_pcamera.z -= _vleft.x * _speed;
	}
	if(l)
		_pcamera += _vleft * _speed;
	if(r)
		_pcamera -= _vleft * _speed;
}
