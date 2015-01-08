#include "Cepe.hpp"

Cepe::Cepe(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram)
	: Mushroom(gProgram, smProgram, "resources/pre-project/cepe.png")
{
	_type = MUSHROOM_CEPE;
}

Cepe::Cepe(Cepe *cepe)
	: Mushroom(cepe)
{
	_type = MUSHROOM_CEPE;
}

Cepe::~Cepe(void)
{
}
