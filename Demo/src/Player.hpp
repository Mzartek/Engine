#ifndef PLAYER
#define PLAYER

namespace Engine
{
	class PlayerCam;
}
class Mushroom;

class Player
{
private:
	Engine::PlayerCam *_cam;
	int _life;
public:
	Player(void);
	~Player(void);
	Engine::PlayerCam *getCamera(void);
	int getLife(void);
	void eatMushroom(Mushroom *mushroom);
	bool isAlive(void);
};

#endif JOUEUR