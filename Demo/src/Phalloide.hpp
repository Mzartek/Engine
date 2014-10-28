#ifndef PHALLOIDE
#define PHALLOIDE

#include "Mushroom.hpp"

class Engine::ShaderProgram;

class Phalloide : public Mushroom
{
public:
	Phalloide(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram);
	Phalloide(Phalloide *phalloide);
	~Phalloide(void);
};

#endif PHALLOIDE
