#include <Engine/FreeCam.hpp>

Engine::FreeCam::FreeCam(void)
{
}

Engine::FreeCam::~FreeCam(void)
{
}

void Engine::FreeCam::keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r)
{
	if(f)
		*_pcamera += *_vforward * _speed;
	if(b)
		*_pcamera -= *_vforward * _speed;
	if(l)
		*_pcamera += *_vleft * _speed;
	if(r)
		*_pcamera -= *_vleft * _speed;

	*_ptarget = *_pcamera + *_vforward;
}
