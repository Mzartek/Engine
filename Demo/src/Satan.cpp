#include "Satan.hpp"

Satan::Satan(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram)
	: Mushroom(gProgram, smProgram, "resources/pre-project/satan.png")
{
	_type = MUSHROOM_SATAN;
}

Satan::Satan(Satan *satan)
	: Mushroom(satan)
{
	_type = MUSHROOM_SATAN;
}

Satan::~Satan(void)
{
}
