#include "Satan.hpp"

Satan::Satan(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram)
	: Mushroom(gProgram, smProgram, "resources/pre-project/satan.png")
{
}

Satan::Satan(Satan *satan)
	: Mushroom(satan)
{
}

Satan::~Satan(void)
{
}

bool Satan::isSatan(void)
{
	return true;
}