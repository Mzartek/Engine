#ifndef CEPE
#define CEPE

#include "Mushroom.hpp"

class Cepe : public Mushroom
{
public:
	Cepe(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram);
	Cepe(Cepe *cepe);
	~Cepe(void);
};

#endif
