#ifndef SMOKEEFFECT_HEADER
#define SMOKEEFFECT_HEADER

#include <Engine/Audio/Sound.hpp>
#include <Engine/Graphics/ParticlesManager.hpp>

class SmokeEffect
{
private:
	Engine::ShaderProgram *_physicsSmokeProgram;
	Engine::ShaderProgram *_displaySmokeProgram;
	Engine::ParticlesManager *_smokeManager;
	Engine::Sound *_fire_sound;
public:
	SmokeEffect(void);
	~SmokeEffect(void);
	void init(const glm::vec3 &position, const unsigned int &numParticles) const;
	void setPosition(const glm::vec3 &pos);
	Engine::ParticlesManager *getParticlesManager(void) const;
	Engine::Sound *getSound(void) const;
};

#endif