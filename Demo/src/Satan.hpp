#ifndef SATAN
#define SATAN

#include "Mushroom.hpp"

class Satan : public Mushroom
{
public:
	Satan(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram);
	Satan(Satan *satan);
	~Satan(void);
	bool isSatan(void);
};

#endif
