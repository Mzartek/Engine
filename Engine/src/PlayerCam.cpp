#include <Engine/PlayerCam.hpp>

engine::PlayerCam::PlayerCam(void)
{
}

engine::PlayerCam::~PlayerCam(void)
{
}

void engine::PlayerCam::keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r)
{
	if(f)
	{
		_pcamera->x -= _vleft->z * _speed;
		_pcamera->z += _vleft->x * _speed;
	}
	if(b)
	{
		_pcamera->x += _vleft->z * _speed;
		_pcamera->z -= _vleft->x * _speed;
	}
	if(l)
		*_pcamera += *_vleft * _speed;
	if(r)
		*_pcamera -= *_vleft * _speed;

	*_ptarget = *_pcamera + *_vforward;
}
