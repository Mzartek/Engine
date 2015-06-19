#ifndef EXPLOSIONEFFECT_HEADER
#define EXPLOSIONEFFECT_HEADER

#include <Engine/Audio/Sound.hpp>
#include <Engine/Graphics/ParticlesHandler.hpp>

using namespace Engine;

class ExplosionEffect
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _physicsProgram;
	std::shared_ptr<Graphics::ShaderProgram> _displayProgram;
	std::shared_ptr<Graphics::ParticlesHandler> _particlesManager;
	std::shared_ptr<Audio::Sound> _sound;

public:
	ExplosionEffect(void);
	~ExplosionEffect(void);
	void init(const glm::vec3 &position, GLuint numParticles);
	void setPosition(const glm::vec3 &pos);
	const std::shared_ptr<Graphics::ParticlesHandler> &getParticlesHandler(void) const;
	const std::shared_ptr<Audio::Sound> &getSound(void) const;
	void updateParticles(void) const;
};

#endif