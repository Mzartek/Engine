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
		_pcamera += _vforward * _speed;
	if (b)
		_pcamera -= _vforward * _speed;
	if (l)
		_pcamera += _vleft * _speed;
	if (r)
		_pcamera -= _vleft * _speed;
}
