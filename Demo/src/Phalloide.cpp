#include "Phalloide.hpp"

Phalloide::Phalloide(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram)
	: Mushroom(gProgram, smProgram, "../share/Demo/resources/textures/phalloide.png")
{
}

Phalloide::Phalloide(Phalloide *phalloide)
	: Mushroom(phalloide)
{
}

Phalloide::~Phalloide(void)
{
}

bool Phalloide::isPhalloide(void)
{
	return true;
}
