#ifndef SMOKEEFFECT_HEADER
#define SMOKEEFFECT_HEADER

#include <Engine/Audio/Sound.hpp>
#include <Engine/Graphics/ParticlesManager.hpp>

class SmokeEffect
{
private:
	std::shared_ptr<Engine::ShaderProgram> _physicsProgram;
	std::shared_ptr<Engine::ShaderProgram> _displayProgram;
	std::shared_ptr<Engine::ParticlesManager> _manager;
	std::shared_ptr<Engine::Sound> _sound;

public:
	SmokeEffect(void);
	~SmokeEffect(void);
	void init(const glm::vec3 &position, GLuint numParticles);
	void setPosition(const glm::vec3 &pos);
	const std::shared_ptr<Engine::ParticlesManager> &getParticlesManager(void) const;
	const std::shared_ptr<Engine::Sound> &getSound(void) const;
	void updateParticles(void) const;
};

#endif
