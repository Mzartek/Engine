#include "Player.hpp"
#include <Engine/PlayerCam.hpp>
#include "Mushroom.hpp"

Player::Player(void)
	: _life(20)
{
	_cam = new Engine::PlayerCam();
}

Player::~Player(void)
{
	delete _cam;
}

Engine::PlayerCam *Player::getCamera(void)
{
	return _cam;
}

int Player::getLife(void)
{
	return _life;
}

void Player::eatMushroom(Mushroom *mushroom)
{
	if (mushroom->isCepe())
		_life = ((_life + 2) <= 20) ? (_life + 2) : 20;
	else if (mushroom->isPhalloide())
		_life = ((_life - 2) >= 0) ? (_life - 2) : 0;
	else if (mushroom->isSatan())
		_life = 0;
}

bool Player::isAlive(void)
{
	return (_life == 0) ? false : true;
}
