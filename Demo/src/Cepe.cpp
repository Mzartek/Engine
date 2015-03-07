#include "Cepe.hpp"

Cepe::Cepe(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram)
	: Mushroom(gProgram, smProgram, "resources/pre-project/cepe.png")
{
}

Cepe::Cepe(Cepe *cepe)
	: Mushroom(cepe)
{
}

Cepe::~Cepe(void)
{
}

bool Cepe::isCepe(void)
{
	return true;
}