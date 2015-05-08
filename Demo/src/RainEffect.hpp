#ifndef RAINEFFECT_HEADER
#define RAINEFFECT_HEADER

#include <Engine/Audio/Sound.hpp>
#include <Engine/Graphics/ParticlesManager.hpp>

class RainEffect
{
private:
	std::shared_ptr<Engine::ShaderProgram> _physicsRainProgram;
	std::shared_ptr<Engine::ShaderProgram> _displayRainProgram;
	std::shared_ptr<Engine::ParticlesManager> _rainManager;
	std::shared_ptr<Engine::Sound> _rain_sound;

public:
	RainEffect(void);
	~RainEffect(void);
	void init(const glm::vec3 &position, GLuint numParticles) const;
	const std::shared_ptr<Engine::ParticlesManager> &getParticlesManager(void) const;
	const std::shared_ptr<Engine::Sound> &getSound(void) const;
};

#endif