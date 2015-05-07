#include <Engine/Graphics/FreeCam.hpp>

Engine::FreeCam::FreeCam(void)
{
}

Engine::FreeCam::FreeCam(GLfloat atheta, GLfloat aphi)
    : MovableCamera(atheta, aphi)
{
}

Engine::FreeCam::~FreeCam(void)
{
}

void Engine::FreeCam::keyboardMove(GLboolean f, GLboolean b, GLboolean l, GLboolean r) const
{
	if(f)
		*_pcamera += *_vforward * _speed;
	if(b)
		*_pcamera -= *_vforward * _speed;
	if(l)
		*_pcamera += *_vleft * _speed;
	if(r)
		*_pcamera -= *_vleft * _speed;
}
