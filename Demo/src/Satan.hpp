#ifndef SATAN
#define SATAN

#include "Mushroom.hpp"

class Engine::ShaderProgram;

class Satan : public Mushroom
{
public:
	Satan(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram);
	Satan(Satan *satan);
	~Satan(void);
};

#endif SATAN
