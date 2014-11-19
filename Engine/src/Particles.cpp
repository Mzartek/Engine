#include <Engine/Particles.hpp>
#include <Engine/ShaderProgram.hpp>

Engine::Particles::Particles(ShaderProgram *program)
	: _numElement(0)
{
	_program = program;

	glGenVertexArrays(1, &_idVAO);
}

Engine::Particles::~Particles(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}