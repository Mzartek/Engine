#include <Engine/Particles.hpp>

Engine::Particles::Particles(ShaderProgram *program)
{
	_program = program;

	_numElement = 0;
	glGenVertexArrays(1, &_idVAO);
}

Engine::Particles::~Particles(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}