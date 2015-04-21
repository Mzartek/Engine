#ifndef RAINEFFECT_HEADER
#define RAINEFFECT_HEADER

#include <Engine/Engine.hpp>

class RainEffect
{
private:
	Engine::ShaderProgram *_physicsRainProgram;
	Engine::ShaderProgram *_displayRainProgram;
	Engine::ParticlesManager *_rainManager;
	Engine::Sound *_rain_sound;
public:
	RainEffect(void);
	~RainEffect(void);
	void init(const glm::vec3 &position, const unsigned int &numParticles) const;
	Engine::ParticlesManager *getParticlesManager(void) const;
	Engine::Sound *getSound(void) const;
};

#endif