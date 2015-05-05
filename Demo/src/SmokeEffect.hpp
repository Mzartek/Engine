#ifndef SMOKEEFFECT_HEADER
#define SMOKEEFFECT_HEADER

#include <Engine/Audio/Sound.hpp>
#include <Engine/Graphics/ParticlesManager.hpp>

class SmokeEffect
{
private:
	std::shared_ptr<Engine::ShaderProgram> _physicsSmokeProgram;
	std::shared_ptr<Engine::ShaderProgram> _displaySmokeProgram;
	std::shared_ptr<Engine::ParticlesManager> _smokeManager;
	std::shared_ptr<Engine::Sound> _fire_sound;
public:
	SmokeEffect(void);
	~SmokeEffect(void);
	void init(const std::shared_ptr<glm::vec3> &position, GLuint numParticles) const;
	void setPosition(const std::shared_ptr<glm::vec3> &pos);
	const std::shared_ptr<Engine::ParticlesManager> &getParticlesManager(void) const;
	const std::shared_ptr<Engine::Sound> &getSound(void) const;
};

#endif