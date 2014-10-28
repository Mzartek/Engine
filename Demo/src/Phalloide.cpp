#include "Phalloide.hpp"

Phalloide::Phalloide(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram)
	: Mushroom(gProgram, smProgram, "resources/pre-project/phalloide.png")
{
	_type = MUSHROOM_PHALLOIDE;
}

Phalloide::Phalloide(Phalloide *phalloide)
	: Mushroom(phalloide)
{
	_type = MUSHROOM_PHALLOIDE;
}

Phalloide::~Phalloide(void)
{
}
