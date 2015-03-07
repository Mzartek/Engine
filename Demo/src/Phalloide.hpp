#ifndef PHALLOIDE
#define PHALLOIDE

#include "Mushroom.hpp"

class Phalloide : public Mushroom
{
public:
	Phalloide(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram);
	Phalloide(Phalloide *phalloide);
	~Phalloide(void);
	bool isPhalloide(void);
};

#endif
